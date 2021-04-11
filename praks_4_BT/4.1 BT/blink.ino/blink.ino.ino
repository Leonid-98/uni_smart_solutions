String data;
String state;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  Serial.println("Initial");
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    data = Serial.readStringUntil("\n");
    if (data == "1") {
      digitalWrite(13, HIGH);
      state = "Led is on";
      Serial.println("Turning on");
    }
    if (data == "0") {
      digitalWrite(13, LOW);
      state = "Led is off";
      Serial.println("Turning off");
    }
    if (data == "State") {
      Serial.println(state);
    }
    

  }

  delay(100);
}
