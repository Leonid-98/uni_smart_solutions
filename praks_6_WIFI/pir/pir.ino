const int pir_pin = D7;
bool in_motion = false;

void setup()
{
  Serial.begin(9600);
  pinMode(pir_pin, INPUT);
}

void loop() {
  //  if (digitalRead(pir_pin) == HIGH  &&  !in_motion) {
  //    Serial.println("Motion detected!");
  //    in_motion = true;
  //  }
  //
  //  if (digitalRead(pir_pin) == LOW  &&  in_motion) {
  //    Serial.println("No movement anymore");
  //    in_motion = false;
  //  }

  if (digitalRead(pir_pin) == HIGH) {
    Serial.println("Movement");
  }
  if (digitalRead(pir_pin) == LOW) {
    Serial.println("No movement");
  }

  delay(500);
}
