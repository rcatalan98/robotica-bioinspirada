#include "LDR.h"

LDR::LDR(int pin)
{
    this->pin = pin;
}

int LDR::getLight()
{
    return analogRead(this->pin);
}
