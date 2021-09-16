#include <SoftwareSerial.h>
int state = 0;
SoftwareSerial mySerial(5, 6);
String data;
int led = 12;


void setup() {
pinMode(led, OUTPUT);
mySerial.begin(9600);
Serial.begin(9600);
}

void loop() {
  if (mySerial.available()){
    data = mySerial.readStringUntil('\n');
    Serial.println(data);

    if (data == "on"){
      Serial.println("led on");
      if (state == 0){
        digitalWrite(led, HIGH);
        mySerial.println("Led is on now");
        state = 1;
      }
      else{
        mySerial.println("Led is already on");
      }
    }
    else if (data ==  "off"){
      if (state == 1){
        digitalWrite(led, LOW);
        mySerial.println("Led is off now");
        state = 0;
      }
      else{
        mySerial.println("Led is already off");
      }
    }
    else if (data == "state"){
      if (state == 0){
        mySerial.println("Led is off");
      }
      else{
        mySerial.println("Led is on");
      }
    }
  }  

  delay(500);
  
  if (Serial.available()){
    mySerial.println(Serial.readStringUntil('\n'));}
}
