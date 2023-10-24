#ifndef EYE_H
#define EYE_H

#include <Arduino.h>
#include <Servo.h>
#include "LDR.h"

class Eye
{
private:
    LDR ldr;
    Servo upDownServo;
    Servo rightLeftServo;
    float prevUpDownPos;

    bool isLight();
    void closeEye();
    void openEye();
    int getVerticalPosition(int value);
    int getSmoothPosition(int value);

public:
  Eye(Servo upDownServo, Servo rightLeftServo, LDR ldr);

  void run();
    
};

#endif