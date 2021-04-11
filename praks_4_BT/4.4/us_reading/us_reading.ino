#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // rx tx

//#define trigPin 8
//#define echoPin 7
//long duration;
//int distance;
//String data;

void setup() {
  //  pinMode(trigPin, OUTPUT);
  //  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() {
  //  digitalWrite(trigPin, LOW);
  //  delayMicroseconds(5);
  //  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(10);
  //  digitalWrite(trigPin, LOW);
  //  duration = pulseIn(echoPin, HIGH);
  //  distance = microsecondsToCentimeters(duration);
  int distance = random(200); // temp
  if (mySerial.available()) {
    mySerial.parseInt();
    mySerial.println(distance);
  }
}


int microsecondsToCentimeters(long microseconds) {
  return microseconds * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}
