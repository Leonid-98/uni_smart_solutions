#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
int data;
LiquidCrystal_I2C lcd(0x27, 20, 4);

SoftwareSerial mySerial(2, 3); // rx tx

void setup() {
  lcd.init();                      
  lcd.backlight();
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() {
  mySerial.println("");
  
  if (mySerial.available()) {
    data = mySerial.parseInt();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(data);
    lcd.print(" cm");
    }
   delay(50);
}
