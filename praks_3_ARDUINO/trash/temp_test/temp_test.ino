#include <SoftwareSerial.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
SoftwareSerial mySerial(5,6);
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
long temp;

void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  sensors.begin();
}
void loop() {
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);
  Serial.println(temp);
  mySerial.println(temp);
  delay(100);
}
