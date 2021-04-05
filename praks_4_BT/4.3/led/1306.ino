#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 7
Adafruit_SSD1306 display(OLED_RESET);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

String data;

void setup() {
  
  mySerial.begin(9600);
  
  Serial.begin(9600);
  Serial.println("Initial");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void loop() {
  if (Serial.available() > 0) {
    data = Serial.readStringUntil("\n");
    showData(data);
  }

  delay(50);
}

void showData(String data) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(data);
  display.display();
}
