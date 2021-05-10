#include <ESP8266WiFi.h>
char ssid[] = "ESP_Leonid";           // SSID of your AP
char pass[] = "11112222";         // password of your AP

IPAddress server(192, 168, 4, 15);  // IP address of the AP
WiFiClient client;

#define trigPin D8
#define echoPin D7
long duration;
int distance;

bool led_state = false;
bool in_motion = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // ms
  distance = duration * 0.034 / 2;

  if (distance <= 20  &&  !in_motion) {
    client.connect(server, 80);

    led_state = !led_state;
    if (led_state) {
      client.println("us_on\r");;
    } else {
      client.println("us_off\r");
    }

    client.flush();
    client.stop();
    in_motion = true;
  }
  if (distance > 20  &&  in_motion) {
    in_motion = false;
  }

  //String answer = client.readStringUntil('\r');
  //Serial.println("From the AP: " + answer);
  delay(500);
}
