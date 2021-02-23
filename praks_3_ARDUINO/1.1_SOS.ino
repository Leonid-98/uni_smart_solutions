int short_delay = 300;
int long_delay = 700;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}
 
void loop() {
  blinkLed(short_delay);
  blinkLed(long_delay);
  blinkLed(short_delay);
  delay(1000)
}
 
void blinkLed(int sleep) {
  for (int i = 0; i < 3; i++){
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(sleep);              
    digitalWrite(LED_BUILTIN, LOW);    
    delay(sleep);
  }
  
}