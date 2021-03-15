void setup() {
  Serial.begin(9600);
  }

void loop(){
  float sens = analogRead(A0);
  Serial.println(sens * 5.0 / 1023.0);
  delay(50);
  
  }
