#ifndef ENGINE_H
#define ENGINE_H

#include <Arduino.h>

#include "Engine.h"

enum ENGINE_DIRECTION
{
    FORWARDS,
    BACKWARDS
};

class Engine
{
private:
    int speedPin;
    int enableAPin;
    int enableBPin;
    int speed;
    ENGINE_DIRECTION direction;

public:
    Engine(int speedPin, int enableAPin, int enableBPin);
    void setSpeed(int speed);
    void setDirection(ENGINE_DIRECTION direction);
    void stop();
    void goForwards();
    void goBackwards();
};

#endif