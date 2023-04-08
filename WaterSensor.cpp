#include <Arduino.h>
#include "WaterSensor.h"

WaterSensor::WaterSensor(byte powerPinNumber, byte inputPinNumber)
{
    _powerPinNumber = powerPinNumber;
    _inputPinNumber = inputPinNumber;

    pinMode(_powerPinNumber, OUTPUT);
}

byte WaterSensor::getPowerPinNumber()
{
    return _powerPinNumber;
}

byte WaterSensor::getInputPinNumber()
{
    return _inputPinNumber;
}

void WaterSensor::turnSensorOn()
{
    digitalWrite(_powerPinNumber, LOW);
}

void WaterSensor::turnSensorOff()
{
    digitalWrite(_powerPinNumber, HIGH);
}

unsigned int WaterSensor::getInputValue()
{
    return analogRead(_inputPinNumber);
}
