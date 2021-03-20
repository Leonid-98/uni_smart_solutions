#include <OneWire.h> 
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
long temp;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  Serial.println("Initial message");
}
void loop() {
  Serial.println("Working");
  
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);
  Serial.println(temp);
  delay(100);
}
