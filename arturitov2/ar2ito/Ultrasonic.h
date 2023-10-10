#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class Ultrasonic
{
private:
    int trigPin;
    int echoPin;

public:
    Ultrasonic(int trigPin, int echoPin);
    float getDistance();
};

#endif
