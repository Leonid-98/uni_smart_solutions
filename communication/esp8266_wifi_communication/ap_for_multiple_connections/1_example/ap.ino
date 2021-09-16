const int ledPin =  LED_BUILTIN; 

boolean start_timer = false;
unsigned long timer_start;
unsigned long timer_end;
String led_state = "off";

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
	if (start_timer) {
		timer_end = millis();
		int time = timer_end - timer_start;
		Serial.println(time);
		led_state = "on";
		if (time > 10000) {
			start_timer = false;
			led_state = "off";
		}
	}
	
	if (Serial.available()) {
		String request = Serial.readStringUntil('\n');
		if (request.equals("pir")){
			start_timer = true;
          	timer_start = millis();
		}
		
		if (request.equals("us_on")){
          	if (start_timer) {
				start_timer = false;
				led_state = "on";
				//timer_start = millis();
			} else {
				led_state = "on";
			}
		}
		
		if (request.equals("us_off")){
          	if (start_timer) {
				start_timer = false;
				led_state = "off";
			} else {
				led_state = "off";
			}
		}
  }
  delay(1000);
  Serial.println(led_state);
}