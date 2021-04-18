#include <IRremote.h>

int led = 5;
int RECV_PIN = 11;
boolean state = false;

IRrecv irrecv(RECV_PIN);
decode_results results;


void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value != 0xFFFFFFFF) {
      turnLed();
    }
    irrecv.resume();
  }
}

void turnLed() {
  if (!state) {
    digitalWrite(led, HIGH);
    state = true;
    return;
  }
  if (state) {
    digitalWrite(led, LOW);
    state = false;
    return;
  }
}
