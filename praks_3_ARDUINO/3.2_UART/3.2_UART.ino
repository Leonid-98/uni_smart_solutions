String data;

void setup() {
	Serial.begin(9600);
	Serial.println("Arduino is ready: ");
}

void loop() {
	while (Serial.available() > 0) {
		char rec = Serial.read();
		data += rec;
		
		if (rec == '\n') {
			Serial.println(data);
			data = "";
		}
	}
	delay(10);
}
