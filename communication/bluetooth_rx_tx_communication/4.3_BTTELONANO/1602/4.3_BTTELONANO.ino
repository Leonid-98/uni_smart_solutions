#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // rx, tx
String data;

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup()
{
  mySerial.begin(9600);
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  Serial.begin(9600);

}

void loop()
{
  if (Serial.available()) {
    data = Serial.readStringUntil("\n");
    lcd.clear();
    lcd.print(data);
  }
  
  if (mySerial.available()) {
    data = mySerial.readStringUntil("\n");
    lcd.clear();
    lcd.print(data);
  }
  delay(100);
}
