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
String us_state = "off";
boolean led_on = false;
int count = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP_Leonid", "11112222");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();

  Serial.println();
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);

  if (request.equals("us_on")) {
    us_state = "on";
  }
  if (request.equals("us_off")) {
    us_state = "off";
  }

  if (request.equals("pir")) {
    led_on = true;

  }
  if (led_on) {
    ledOn();
  }

  if (request.equals("led"))  {
    client.println(us_state + "\r");
  }
  Serial.println(us_state);

}

void ledOn() {
  if (count < 10) {
    us_state = "on";
    delay(1);
    count++;
  } else {
    count = 0;
    led_on = false;
    us_state = "off";
  }
}
