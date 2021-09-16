
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6);

#include <FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 3
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];

long temp;
String data;


void setup() {
mySerial.begin(9600);
Serial.begin(9600);
FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);

  int r = map(temp, 18, 35, 0, 255);
  int b = 255 - r;
  int g = 0;
  leds[0] = CRGB(g, r, b);
  FastLED.show();
  
  if (mySerial.available()){
    data = mySerial.readStringUntil('\n');
    mySerial.println(temp);
  } 
  
  if (Serial.available()){
    mySerial.println(Serial.readStringUntil('\n'));
    }
  
  delay(500);
}
