#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "HUAWEI_P30"
#define STAPSK  "11113333"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.43.164";
const uint16_t port = 1234;

int trigPin = D4;
int echoPin = D3;
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  WiFi.begin(ssid, password);
  delay(3000);
}

void loop() {
  WiFiClient client;
  if (!client.connect(host, port)) {
    delay(3000);
  }

  if (client.connected()) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    client.print(distance);
    delay(2000);
    client.stop();
  }

}
