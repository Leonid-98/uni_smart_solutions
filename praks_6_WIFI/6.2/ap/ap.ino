/*  Accesspoint - station communication without router
    see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-class.rst
         https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-examples.rst
         https://github.com/esp8266/Arduino/issues/504
    Works with: station_bare_01.ino
*/


#include <ESP8266WiFi.h>

WiFiServer server(80);
IPAddress IP(192, 168, 4, 15);
IPAddress mask = (255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP_Leonid", "11112222");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();

  Serial.println();
  Serial.println("accesspoint_bare_01.ino");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
}

void loop() {
  //  WiFiClient client = server.available();
  //  if (!client) {return;}
  //
  //  String request = client.readStringUntil('\r');
  //  Serial.println("********************************");
  //  Serial.println("From the station: " + request);
  //  client.flush();
  //  Serial.print("Byte sent to the station: ");
  //  Serial.println(client.println(request + "ca" + "\r"));
  //  String saadetud=Serial.readString();
  //  client.println(saadetud+"\r");
  //  Serial.println(saadetud);
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  if (request.equals("us_on")) {
    Serial.println("Turning led on");
  }
  if (request.equals("us_off")) {
    Serial.println("Turning led off");
  }

  if (request.equals("pir")) {
    Serial.println("Movement detected");
    client.println("Ap responce\r");
  }

  client.flush();

}
