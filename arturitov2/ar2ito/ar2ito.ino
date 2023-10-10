#include "Car.h"
#include "Engine.h"
#include "Ultrasonic.h"
#include "LDR.h"

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

// 💡
const int ldrPin = 0;


Engine leftEngine(enB, in3, in4);
Engine rightEngine(enA, in1, in2);

Ultrasonic ultrasonic(trigPin, echoPin);
LDR ldr(ldrPin);

Car car(leftEngine, rightEngine, ultrasonic, ldr);


void setup() {
  Serial.begin(9600);
}

void loop() {
  car.run();
  delay(100);

}
