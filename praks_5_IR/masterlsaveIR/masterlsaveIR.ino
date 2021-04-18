//  Include following libraries to access IR sensor
#include <IRremote.h>
#include <IRremoteInt.h>

const int OUT = 8;
int RECV_PIN = 4;
boolean state = false;

IRrecv receiver(RECV_PIN);
decode_results results;

void setup() {
  pinMode(OUT, OUTPUT);
  receiver.enableIRIn();
}

void loop() {
  if (receiver.decode(&results)) {
    if (state) {
      digitalWrite(OUT, LOW);
      state = false;
    }

    if (!state) {
      digitalWrite(OUT, HIGH);
      state = true;
    }
  }
  delay(500);
  receiver.resume();
  Serial.println(state);
}
