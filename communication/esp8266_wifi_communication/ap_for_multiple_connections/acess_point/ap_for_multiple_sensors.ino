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

boolean start_timer = false;
unsigned long timer_start;
unsigned long timer_end;
String led_state = "off";

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
	
	if (start_timer) {
		timer_end = millis();
		int time = timer_end - timer_start;
		Serial.println(time);
		led_state = "on";
		if (time > 10000) {
			start_timer = false;
			led_state = "off";
		}
	}
	
	if (request.equals("led"))  {
	client.println(led_state + "\r");
	}
	
	if (request.equals("pir")){
			start_timer = true;
          	timer_start = millis();
		}
		
	
	if (request.equals("us_on")){
          	if (start_timer) {
				start_timer = false;
				led_state = "on";
				//timer_start = millis();
			} else {
				led_state = "on";
			}
		}

	if (request.equals("us_off")){
          	if (start_timer) {
				start_timer = false;
				led_state = "off";
			} else {
				led_state = "off";
			}
		}
 } 
 Serial.println(us_state);
}
