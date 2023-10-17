//include library for servo
#include <Servo.h>

//define name of the servo motors
Servo upDownServo;
Servo rightLeftServo;

//define position name and value
#define left 60
#define right 120
#define middle 90
#define closed 60
#define fullOpen 180
#define halfOpen 160

#define waitTime 760


void setup(){
  //define pin numbers of the servo motors
  upDownServo.attach(2);
  rightLeftServo.attach(6);

  //starting position of the servo motors
  delay(10);
  upDownServo.write(closed);
  rightLeftServo.write(middle);
}

void loop(){
  
  delay(500);
  upDownServo.write(halfOpen);
  delay(waitTime);
  rightLeftServo.write(right);
  delay(waitTime);
  rightLeftServo.write(left);
  delay(waitTime);
  rightLeftServo.write(middle);

  delay(500);
  upDownServo.write(closed);
  delay(waitTime);
  upDownServo.write(fullOpen);
  delay(waitTime);
  upDownServo.write(closed);
  delay(waitTime);
  upDownServo.write(fullOpen);
  delay(waitTime);
  rightLeftServo.write(right);
  delay(waitTime);
  rightLeftServo.write(left);
  delay(waitTime);
  rightLeftServo.write(middle);
  upDownServo.write(halfOpen);
  delay(waitTime);
  rightLeftServo.write(right);
  delay(waitTime);
  rightLeftServo.write(left);
  delay(waitTime);
  rightLeftServo.write(middle);
  delay(waitTime);
  upDownServo.write(fullOpen);
  delay(waitTime);
  upDownServo.write(halfOpen);
  delay(waitTime);
  upDownServo.write(fullOpen);
  delay(waitTime);
  rightLeftServo.write(right);
  delay(waitTime);
  rightLeftServo.write(left);
  delay(waitTime);
  rightLeftServo.write(middle);
}
