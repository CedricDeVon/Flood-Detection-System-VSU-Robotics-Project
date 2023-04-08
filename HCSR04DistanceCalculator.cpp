#include <Arduino.h>
#include "HCSR04DistanceCalculator.h"

unsigned int HCSR04DistanceCalculator::getIntegerConversion(unsigned int analogInput, byte index)
{
    if (_isIndexInvalid(index))
    {
        return NULL;
    }
    else
    {
        return analogInput / _valueEquivalents[index];
    }
}

char *HCSR04DistanceCalculator::getStringEquivalent(byte index)
{
    if (_isIndexInvalid(index))
    {
        return NULL;
    }
    else
    {
        return _stringEquivalents[index];
    }
}

bool HCSR04DistanceCalculator::_isIndexInvalid(byte index)
{
    return index < 0 || index >= sizeof(_stringEquivalents) / sizeof(_stringEquivalents[0]);
}
