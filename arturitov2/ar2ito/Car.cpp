#include "Car.h"

Car::Car(Engine rightEngine, Engine leftEngine, Ultrasonic ultrasonic, LDR ldr)
    : rightEngine(rightEngine), leftEngine(leftEngine), ultrasonic(ultrasonic), ldr(ldr)
{
    this->speed = 0;
    this->lastUpdate = millis();
}

void Car::setSpeed(int speed)
{
    this->speed = speed;
    this->rightEngine.setSpeed(this->speed);
    this->leftEngine.setSpeed(this->speed);
}

void Car::stop()
{
    this->rightEngine.stop();
    this->leftEngine.stop();
}

void Car::goForwards()
{
    this->rightEngine.goForwards();
    this->leftEngine.goForwards();
}

void Car::goBackwards()
{
    this->rightEngine.goBackwards();
    this->leftEngine.goBackwards();
}

void Car::turnLeft()
{
    this->rightEngine.goForwards();
    this->leftEngine.goBackwards();
}

void Car::turnRight()
{
    this->rightEngine.goBackwards();
    this->leftEngine.goForwards();
}

bool Car::isObstacle()
{
    float distance = this->ultrasonic.getDistance();
    Serial.print("Ultrasonic: ");
    Serial.println(distance);
    return distance < 25;
}

bool Car::isLight() 
{
  int light = this->ldr.getLight();
  Serial.print("Light: ");
  Serial.println(light);
  return light > 500;
}

void Car::run()
{
    bool shouldEvade = !isLight();
    unsigned long currentTime = millis();

    if (shouldEvade)
    {
        if (currentTime - lastUpdate < 500)
        {
            setSpeed(80);
            goBackwards();
            //Serial.println("BACKWARDS");
        }
        else if (currentTime - lastUpdate < 1200)
        {
            setSpeed(80);
            turnLeft();
            //Serial.println("LEFT");
        }
        else
        {
            lastUpdate = currentTime;
        }
    }
    else
    {
        setSpeed(120);
        goForwards();
        //Serial.println("FORWARDS");
    }
}
