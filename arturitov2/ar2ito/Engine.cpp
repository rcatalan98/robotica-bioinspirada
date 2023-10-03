#include "Engine.h"

Engine::Engine(int speedPin, int enableAPin, int enableBPin)
{
    this->speedPin = speedPin;
    this->enableAPin = enableAPin;
    this->enableBPin = enableBPin;

    pinMode(this->speedPin, OUTPUT);
    pinMode(this->enableAPin, OUTPUT);
    pinMode(this->enableBPin, OUTPUT);

    this->speed = 0;
    this->direction = ENGINE_DIRECTION::FORWARDS;
}

void Engine::setSpeed(int speed)
{
    this->speed = speed;
    analogWrite(this->speedPin, this->speed);
}

void Engine::setDirection(ENGINE_DIRECTION direction)
{
    this->direction = direction;

    switch (this->direction)
    {
    case ENGINE_DIRECTION::FORWARDS:
        digitalWrite(this->enableAPin, LOW);
        digitalWrite(this->enableBPin, HIGH);
        break;
    case ENGINE_DIRECTION::BACKWARDS:
        digitalWrite(this->enableAPin, HIGH);
        digitalWrite(this->enableBPin, LOW);
        break;
    }
}

void Engine::stop()
{
    this->setSpeed(0);
}

void Engine::goForwards()
{
    this->setDirection(ENGINE_DIRECTION::FORWARDS);
}

void Engine::goBackwards()
{
    this->setDirection(ENGINE_DIRECTION::BACKWARDS);
}
