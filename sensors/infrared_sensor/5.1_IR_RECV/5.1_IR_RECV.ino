//  Include following libraries to access IR sensor
#include <IRremote.h>
#include <IRremoteInt.h>

const int OUT = 5;
int RECV_PIN = 11;

IRrecv receiver(RECV_PIN);
decode_results results;

void setup() {
  pinMode(OUT, OUTPUT);
  receiver.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  if (receiver.decode(&results)) {
    if (results.value == 0x29D) {
      digitalWrite(OUT, HIGH);
    }
    if (results.value == 0x25D) {
      digitalWrite(OUT, LOW);
    }
    Serial.println(results.value, HEX);
    receiver.resume();
  }
}
