/*
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10
unsigned long tags[2] = {0xFFFFB71E, 0xFFFFA81B};
unsigned long hex_num;

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo;
int pos = 0;



void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  servo.attach(7);
  servo.write(0);
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  Serial.println(hex_num, HEX);

  if (isAccess()) {
    Serial.println("Autorized access!");
    openTheDoor();
  } else {
    Serial.println("Access denied!");
  }


}

boolean isAccess() {
  for (long elem : tags) {
    if (hex_num == elem) {
      return true;
    }
  }
  return false;
}

void openTheDoor() {
  for (pos = 0; pos <= 90; pos += 1) {
    servo.write(pos);
    delay(20);
  }
  delay(3000);
  for (pos = 90; pos >= 0; pos -= 1) {
    servo.write(pos);
    delay(20);
  }
}
