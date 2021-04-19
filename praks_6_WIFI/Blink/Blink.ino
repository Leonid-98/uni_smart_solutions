#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <string.h>


bool connectToBase();

std::string ssid = "HUAWEI_p30";
std::string pass = "123456789";
IPAddress server(192,168,43,58);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  //WiFi.mode(WIFI_STA);
 
  Serial.print("Connecting to ");
  Serial.println(ssid.c_str());
  Serial.println(WiFi.begin(ssid.c_str(), pass.c_str()));
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Attempting connection");
  while(!client.connect(server, 80)){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected");
}

void loop() {
 
}
