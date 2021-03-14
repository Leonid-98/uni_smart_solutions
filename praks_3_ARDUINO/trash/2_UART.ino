#include <SoftwareSerial.h>
int a = 0;
SoftwareSerial mySerial(4,5);
String sisse;
int led = 13;


void setup() {
pinMode(led, OUTPUT);
mySerial.begin(9600);
Serial.begin(9600);
}

void loop() {
  if (mySerial.available()){
    sisse = mySerial.readStringUntil('\n');
    Serial.println(sisse);

    if (sisse == "polema"){
      Serial.println("sees");
      if (a == 0){
        digitalWrite(led, HIGH);
        mySerial.println("Led pandi polema.");
        a = 1;
      }
      else{
        mySerial.println("Led juba poleb.");
      }
    }
    else if (sisse ==  "kustu"){
      if (a == 1){
        digitalWrite(led, LOW);
        mySerial.println("Led kustutati.");
        a = 0;
      }
      else{
        mySerial.println("Led on juba kustus.");
      }
    }
    else if (sisse == "seis"){
      if (a == 0){
        mySerial.println("Led on kustus.");
      }
      else{
        mySerial.println("Led poleb.");
      }
    }
  }  

  delay(1000);
  if (Serial.available()){
    mySerial.println(Serial.readStringUntil('\n'));}
}