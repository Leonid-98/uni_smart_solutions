


#include <IRremote.h>

IRsend irsend;

String data;
void setup()
{
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    data = Serial.readStringUntil("\n");

    if (data == "on\n") {
      irsend.sendSony(0x25d, 12);
    }

    if (data == "off\n") {
      irsend.sendSony(0x29d, 12);
    }
  }
}
