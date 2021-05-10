#include <ESP8266WiFi.h>

char ssid[] = "ESP_Leonid";           // SSID of your AP
char pass[] = "11112222";         // password of your AP
IPAddress server(192, 168, 4, 15);  // IP address of the AP
WiFiClient client;
#define LED D4


void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

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
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());

}

void loop()
{
  client.connect(server, 80);
  client.println("led\r");

  String answer = client.readStringUntil('\r');
  Serial.println(answer);

  if (answer.equals("on")) {
    Serial.println("Turning led on");
    digitalWrite(LED, HIGH);
  }
  if (answer.equals("off")) {
    Serial.println("Turning led off");
    digitalWrite(LED, LOW);
  }
  client.stop();
  delay(500);
}
