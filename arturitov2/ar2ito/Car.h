#ifndef CAR_H
#define CAR_H

#include <Arduino.h>
#include "Engine.h"
#include "Ultrasonic.h"
#include "LDR.h"

class Car
{
private:
    Engine rightEngine;
    Engine leftEngine;
    Ultrasonic ultrasonic;
    LDR ldr;
    int speed;
    int lastUpdate;

public:
    Car(Engine rightEngine, Engine leftEngine, Ultrasonic ultrasonic, LDR ldr);
    void setSpeed(int speed);
    void stop();
    void goForwards();
    void goBackwards();
    void turnLeft();
    void turnRight();
    bool isObstacle();
    bool isLight();
    void run();
};

#endif
