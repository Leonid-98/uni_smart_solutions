#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#include <ESP8266WiFi.h>
char ssid[] = "ESP_Leonid";           // SSID of your AP
char pass[] = "11112222";         // password of your AP

IPAddress server(192, 168, 4, 15);  // IP address of the AP
WiFiClient client;

bool in_motion = false;

void setup() {
  Serial.begin(115200);
  lox.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  if (measure.RangeStatus != 4) {

    if (measure.RangeMilliMeter <= 1000  &&  !in_motion) {
      client.connect(server, 80);
      Serial.println("motion detected!");

      client.println("pir\r");

      client.flush();
      client.stop();
      in_motion = true;
    }
    if (measure.RangeMilliMeter > 1000  &&  in_motion) {
      in_motion = false;
    }
  }
  delay(100);
}
