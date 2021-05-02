#define trigPin 8
#define echoPin 7
long duration;
int distance;

bool led_state = false;
bool in_motion = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
	digitalWrite(trigPin, LOW);
	delayMicroseconds(5);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = microsecondsToCentimeters(duration);

	if(distance <= 100  &&  !in_motion){
      Serial.println("Motion detected!");
      led_state = !led_state;
      in_motion = true;
    }
    if(distance > 100  &&  in_motion){
      Serial.println("No movement anymore");
      in_motion = false;
    }
	
  	Serial.println(led_state);
    delay(500);
}

int microsecondsToCentimeters(long microseconds) {
  return microseconds * 0.034 / 2;
}
