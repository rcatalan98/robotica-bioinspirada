#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trigPin, int echoPin)
{
    this->trigPin = trigPin;
    this->echoPin = echoPin;

    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
}

float Ultrasonic::getDistance()
{
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigPin, LOW);

    float duration = pulseIn(this->echoPin, HIGH);
    float distance = duration * 0.0343 / 2.0;
    return distance;
}
