#include <Arduino.h>
#include "HCSR04UltrasonicDistanceSensor.h"

HCSR04UltrasonicDistanceSensor::HCSR04UltrasonicDistanceSensor(
    byte inputPinNumber,
    byte outputPinNumber)
{
    _inputPinNumber = inputPinNumber;
    _outputPinNumber = outputPinNumber;
    _receptionDelayInMicroseconds = 10;

    pinMode(_inputPinNumber, INPUT);
    pinMode(_outputPinNumber, OUTPUT);
}

HCSR04UltrasonicDistanceSensor::HCSR04UltrasonicDistanceSensor(
    byte inputPinNumber,
    byte outputPinNumber,
    unsigned int receptionDelayInMicroseconds)
{
    _inputPinNumber = inputPinNumber;
    _outputPinNumber = outputPinNumber;
    _receptionDelayInMicroseconds = receptionDelayInMicroseconds;

    pinMode(_inputPinNumber, INPUT);
    pinMode(_outputPinNumber, OUTPUT);
}

unsigned int HCSR04UltrasonicDistanceSensor::getReceptionDelayInMicroseconds()
{
    return _receptionDelayInMicroseconds;
}

byte HCSR04UltrasonicDistanceSensor::getInputPinNumber()
{
    return _inputPinNumber;
}

byte HCSR04UltrasonicDistanceSensor::getOutputPinNumber()
{
    return _outputPinNumber;
}

unsigned int HCSR04UltrasonicDistanceSensor::getAnalogInput()
{
    digitalWrite(_outputPinNumber, HIGH);
    delayMicroseconds(_receptionDelayInMicroseconds);
    digitalWrite(_outputPinNumber, LOW);
    return pulseIn(_inputPinNumber, HIGH);
}
