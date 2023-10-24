#include "Eye.h"

#define CLOSED 90.0
#define OPEN 180.0
#define LEFT 120
#define RIGHT 40

Eye::Eye(Servo upDownServo, Servo rightLeftServo, LDR ldr)
    : upDownServo(upDownServo), rightLeftServo(rightLeftServo), ldr(ldr)
{
    prevUpDownPos = 90.0;
    upDownServo.write(prevUpDownPos);
}

bool Eye::isLight()
{
  int light = this->ldr.getLight();
  return light > 900;
}

void Eye::closeEye()
{
  upDownServo.write(CLOSED);
}

void Eye::openEye()
{
  upDownServo.write(OPEN);
}

int Eye::getVerticalPosition(int value)
{
  if (value < 0) value = 0;
  if (value > 1023) value = 1023;
  
  double minInput = 300.0;
  double maxInput = 1023.0;
  double minOutput = OPEN;
  double maxOutput = CLOSED;

  double inputRange = maxInput - minInput;
  double outputRange = maxOutput - minOutput;

  // Calculate the mapped value and cast it to an integer
  int mappedValue = static_cast<int>(maxOutput - (value - minInput) * (outputRange / inputRange));

  return mappedValue;
}

int Eye::getSmoothPosition(int value)
{
  float position = (float) getVerticalPosition(value);

  float smoothPosition = (position * 0.1) + (prevUpDownPos * 0.9);

  prevUpDownPos = smoothPosition;
  return smoothPosition;
}

void Eye::run() 
{
  int light = ldr.getLight();
  int position = getSmoothPosition(light);
  Serial.println(position);
  upDownServo.write(position);
  rightLeftServo.write(90);
}