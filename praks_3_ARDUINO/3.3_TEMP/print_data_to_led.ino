#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 7
Adafruit_SSD1306 display(OLED_RESET);

String data;

void setup() {
  Serial.begin(9600);
  Serial.println("Initial");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void loop() {
  if (Serial.available() > 0){
    data = Serial.readString();
    
    Serial.println(data);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(data);
    display.display();
    }
}
