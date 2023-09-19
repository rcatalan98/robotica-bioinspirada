// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B connections
int in3 = 5;
int in4 = 4;
int enB = 3;

int motorA[] = {in1, in2};
int motorB[] = {in3, in4};

// 👀
const int trigPin = 12;
const int echoPin = 11;

float duration, distance;

int count = 0;

enum DIRECTION {
  FORWARDS,
  BACKWARDS,
  RIGHT,
  LEFT
};

void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);

  // crazy eyes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // 👀
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  Serial.print("Distance: ");
  Serial.println(distance);
  
  setSpeed(80);
	setDirection(FORWARDS);

  

  if(distance < 25) {
    // 🛞
		evade();
  }

	delay(1);
}

void evade() {
	setDirection(BACKWARDS);
	delay(700);
	setDirection(LEFT);
	delay(500);
	setDirection(FORWARDS);
}

void setDirection(int direction) {
	switch (direction) {
		case FORWARDS:
			digitalWrite(in1, LOW);
			digitalWrite(in2, HIGH);
			digitalWrite(in3, LOW);
			digitalWrite(in4, HIGH);
      Serial.println("FORWARDS");
			break;

		case BACKWARDS:
			digitalWrite(in1, HIGH);
			digitalWrite(in2, LOW);
			digitalWrite(in3, HIGH);
			digitalWrite(in4, LOW);
      Serial.println("BACKWARDS");

			break;

		case RIGHT:
			digitalWrite(in1, HIGH);
			digitalWrite(in2, LOW);
			digitalWrite(in3, LOW);
			digitalWrite(in4, HIGH);
      Serial.println("RIGHT");

			break;

		case LEFT:
			digitalWrite(in1, LOW);
			digitalWrite(in2, HIGH);
			digitalWrite(in3, HIGH);
			digitalWrite(in4, LOW);
      Serial.println("LEFT");

			break;
	}

}

void setSpeed(int speed) {
	analogWrite(enA, speed);
	analogWrite(enB, speed);
}


// This function lets you control spinning direction of motors
void directionControl() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enA, 255);
	analogWrite(enB, 255);

	// Turn on motor A & B
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	delay(2000);
	
	// Now change motor directions
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	delay(2000);
	
	// Turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

// This function lets you control speed of the motors
void speedControl() {
	// Turn on motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	
	// Accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++) {
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// Decelerate from maximum speed to zero
	for (int i = 255; i >= 0; --i) {
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// Now turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}