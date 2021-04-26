#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "AP-Leonid";
const char* password = "11112222";

AsyncWebServer server(80);

void setup(){
  Serial.begin(115200);
  Serial.println();
  
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/pir", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "pir movement");
  });
  server.on("/us", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "us distance");
  });
  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "led info");
  });
  
  server.begin();
}
 
void loop(){
  
}
