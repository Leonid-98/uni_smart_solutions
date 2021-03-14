int delay_short = 60;
int delay_long = delay_short*3;


void setup() {
  pinMode(3, OUTPUT);
}

void loop() {
  blinkLed(delay_short);  
  blinkLed(delay_short);  
  blinkLed(delay_short);
  delay(150);
  blinkLed(delay_long);  
  blinkLed(delay_long);  
  blinkLed(delay_long);  
  delay(150);
  blinkLed(delay_short);  
  blinkLed(delay_short);  
  blinkLed(delay_short);
  delay(1000);
}

void blinkLed(int sleep) {
  digitalWrite(3, HIGH);
  delay(sleep);
  digitalWrite(3, LOW);
  delay(sleep);
}
