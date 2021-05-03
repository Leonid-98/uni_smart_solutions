// D1 = SCL
// D2 = SDA

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
String data;

LiquidCrystal_I2C lcd(0x27, 20, 4); 

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  Serial.begin(9600);

}

void loop()
{
  if (Serial.available()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    while (Serial.available() > 0) {
      char c = Serial.read();
      data += c;
    }
    data = data.substring(0, data.length() - 1); // eemaldan 2 viimast baiti
    lcd.print(data);
    data = "";
  }
  delay(100);
}
