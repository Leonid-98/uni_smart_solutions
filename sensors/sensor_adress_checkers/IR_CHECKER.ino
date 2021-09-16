#include <IRremote.h>
int receiver = 4;
IRrecv irrecv(receiver);
decode_results results;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
  }


}

// FFA25D - 1
// FF629D - 2
// FFE21D - 3
// FF22DD - 4
