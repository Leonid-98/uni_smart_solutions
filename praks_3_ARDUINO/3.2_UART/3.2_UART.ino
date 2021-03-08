//
//#include "U8glib.h"
//U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);
////U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE); 
//
//void setup(){
//  u8g.setFont(u8g_font_unifont);
//  u8g.setPrintPos(0, 20);}
//
//void loop() {
//  u8g.firstPage();
//  do {
//    u8g.print("123");
//    } while (u8g.nextPage());
//  delay(500);
//
//  }

//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_SSD1306.h>
// 
//#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);
// 
//void setup() {
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//}
// 
//void loop() {
//  display.clearDisplay();
//  display.setTextSize(2);
//  display.setTextColor(WHITE);
//  display.setCursor(0,0);
//  display.print("123");
//  display.display();
//  delay(10000);
//}

String nom = "Arduino";
String msg
