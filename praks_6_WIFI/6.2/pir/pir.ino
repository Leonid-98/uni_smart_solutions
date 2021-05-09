
#include <ESP8266WiFi.h>
char ssid[] = "ESP_Leonid";           // SSID of your AP
char pass[] = "11112222";         // password of your AP

IPAddress server(192, 168, 4, 15);  // IP address of the AP
WiFiClient client;

const int pir_pin = D5;	// DIGITAL
bool in_motion = false;
bool led_state = false;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
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
  pinMode(pir_pin, INPUT);
}

void loop() {
  client.connect(server, 80);

  if (digitalRead(pir_pin) == HIGH  &&  !in_motion) {
    client.println("pir\r");
    in_motion = true;
  }

  if (digitalRead(pir_pin) == LOW   &&  in_motion) {
    in_motion = false;
  }
  delay(2000);
}
