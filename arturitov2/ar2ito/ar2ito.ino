// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B connections
int in3 = 5;
int in4 = 4;
int enB = 3;

// 👀
const int trigPin = 12;
const int echoPin = 11;

const int ldrPin = 0;

int count = 0;

enum DIRECTION {
  FORWARDS,
  BACKWARDS,
  RIGHT,
  LEFT
};

class Engine {
private:
  int speedPin;
  int enableAPin;
  int enableBPin;
  int speed;
  DIRECTION direction;

public:
  Engine(int speedPin, int enableAPin, int enableBPin) {
    pinMode(speedPin, OUTPUT);
    pinMode(enableAPin, OUTPUT);
    pinMode(enableBPin, OUTPUT);
    this->speedPin = speedPin;
    this->enableAPin = enableAPin;
    this->enableBPin = enableBPin;
    this->speed = 0;
    this->direction = FORWARDS;
  }

  void printSpeed() {
    Serial.print("Speed: ");
    Serial.println(speed);
  }

  void setSpeed(int speed) {
    this->speed = speed;
    analogWrite(speedPin, speed);
  }

  void setDirection(DIRECTION direction) {
    this->direction = direction;
    switch (direction) {
      case FORWARDS:
        digitalWrite(enableAPin, LOW);
        digitalWrite(enableBPin, HIGH);
        break;

      case BACKWARDS:
        digitalWrite(enableAPin, HIGH);
        digitalWrite(enableBPin, LOW);
        break;
    }
  }

  void stop() {
    setSpeed(0);
    digitalWrite(enableAPin, LOW);
    digitalWrite(enableBPin, LOW);
  }

  void goForwards() {
    setDirection(FORWARDS);
  }

  void goBackwards() {
    setDirection(BACKWARDS);
  }
};

class Ultrasonic {
private:
  int echoPin;
  int trigPin;

public:
  Ultrasonic(int echoPin, int trigPin) {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    this->echoPin = echoPin;
    this->trigPin = trigPin;
  }

  float getDistance() {
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigPin, LOW);
    float duration = pulseIn(this->echoPin, HIGH);
    float distance = (duration * .0343) / 2;
    return distance;
  }
};

class LDR {
private:
  int pin;

public:
  LDR(int pin) {
    this->pin = pin;
  }

  int getLightValue() {
    return analogRead(this->pin);
  }
};

class Car {
private:
  Engine rightEngine;
  Engine leftEngine;
  Ultrasonic ultrasonic;
  LDR ldr;
  int speed;
  int firstEvasionTime;
  int secondEvasionTime;
  int lastUpdate;

public:
  Car(Engine lEngine, Engine rEngine, Ultrasonic ultrasonic, LDR ldr)
    : leftEngine(lEngine), rightEngine(rEngine),
      ultrasonic(ultrasonic), ldr(ldr) {
    this->speed = 0;
    this->firstEvasionTime = 700;
    this->secondEvasionTime = this->firstEvasionTime + 500;
    this->lastUpdate = millis();
  }

  void setSpeed(int speed) {
    this->speed = speed;
    this->rightEngine.setSpeed(speed);
    this->leftEngine.setSpeed(speed);
  }

  void stop() {
    setSpeed(0);
    this->rightEngine.stop();
    this->leftEngine.stop();
  }

  void setDirection(DIRECTION direction) {
    switch (direction) {
      case FORWARDS:
        this->leftEngine.goForwards();
        this->rightEngine.goForwards();
        break;
      case BACKWARDS:
        this->leftEngine.goBackwards();
        this->rightEngine.goBackwards();
        break;
      case LEFT:
        this->leftEngine.goBackwards();
        this->rightEngine.goForwards();
        break;
      case RIGHT:
        this->leftEngine.goForwards();
        this->rightEngine.goBackwards();
        break;
    }
  }

  void goForwards() {
    setDirection(FORWARDS);
  }

  void goBackwards() {
    setDirection(BACKWARDS);
  }

  void turnRight() {
    setDirection(RIGHT);
  }

  void turnLeft() {
    setDirection(LEFT);
  }

  bool checkEvasion() {
    float distance = this->ultrasonic.getDistance();
    Serial.print("Distance: ");
    Serial.println(distance);
    return distance < 25;
  }

  void run() {
    bool shouldEvade = checkEvasion();
    unsigned long currentTime = millis();

    if (shouldEvade) {
      if (currentTime - lastUpdate < 500) {
        setSpeed(80);
        goBackwards();
        Serial.println("BACKWARDS");
      } else if (currentTime - lastUpdate < 1200) {
        setSpeed(80);
        turnLeft();
        Serial.println("LEFT");
      } else {
        lastUpdate = currentTime;
      }
    } else {
      setSpeed(120);
      goForwards();
      Serial.println("FORWARDS");
    }
  }
};

Engine leftEngine(enB, in3, in4);
Engine rightEngine(enA, in1, in2);

Ultrasonic ultrasonic(echoPin, trigPin);
LDR ldr(ldrPin);

Car car(leftEngine, rightEngine, ultrasonic, ldr);

void setup() {
  Serial.begin(9600);
}

void loop() {
  car.run();
  delay(100);
}
