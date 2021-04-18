//  Include following libraries to access IR sensor
#include <IRremote.h>
#include <IRremoteInt.h>

const int OUT = 8;
int RECV_PIN = 4;

IRrecv receiver(RECV_PIN);
decode_results results;

void setup() {
  pinMode(OUT, OUTPUT);
  receiver.enableIRIn();
}

void loop() {
  if (receiver.decode(&results)) {
    if (results.value == 0xFFA25D) {
      digitalWrite(OUT, HIGH);
    }
    if (results.value == 0xFF629D) {
      digitalWrite(OUT, LOW);
    }
    Serial.println(results.value, HEX);
    receiver.resume();
  }
}
