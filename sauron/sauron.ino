#include <Servo.h>
#include "LDR.h"
#include "Eye.h"

// 💡
const int ldrPin = 0;

LDR ldr(ldrPin);
//define name of the servo motors
Servo upDownServo;
Servo rightLeftServo;

Eye eye(upDownServo, rightLeftServo, ldr);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  upDownServo.attach(3);
  rightLeftServo.attach(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  eye.run();
  delay(100);
}
