// D1 = SCL
// D2 = SDA

#include <Wire.h>
// #include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

//LiquidCrystal_I2C lcd(0x27, 20, 4); 
char ssid[] = "ESP_Leonid";           // SSID of your AP
char pass[] = "11112222";         // password of your AP
IPAddress server(192, 168, 4, 15);  // IP address of the AP
WiFiClient client;
String data;

/**/
  int LED = D8;
/**/

void setup()
{
  //lcd.init();
  //lcd.backlight();
  //lcd.setCursor(0, 0);
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
  
  
  /**/
  pinMode(LED, OUTPUT);
  /**/
}

void loop()
{	
  
  /**/
  digitalWrite(LED, HIGH);
  /**/
    
  client.connect(server, 80);
  
  /*
  if (Serial.available()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    while (Serial.available() > 0) {
      char c = Serial.read();
      data += c;
    }
    data = data.substring(0, data.length() - 1); // eemaldan 2 viimast baiti
    lcd.print(data);
    data = "";
  }
  */
  
  client.println("led\r");
  String answer = client.readStringUntil('\r');
  Serial.println("From the AP: " + answer);
  
  client.flush();
  client.stop();
  delay(2000);
}
