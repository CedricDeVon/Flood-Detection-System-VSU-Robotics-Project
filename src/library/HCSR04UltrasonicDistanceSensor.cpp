#include <Arduino.h>

#include "HCSR04UltrasonicDistanceSensor.h"

HCSR04UltrasonicDistanceSensor::HCSR04UltrasonicDistanceSensor(
    byte triggerPinNumber,
    byte echoPinNumber,
    unsigned int receptionDelayInMicroseconds)
{
    _triggerPinNumber = triggerPinNumber;
    _echoPinNumber = echoPinNumber;
    _receptionDelayInMicroseconds = receptionDelayInMicroseconds;

    pinMode(_triggerPinNumber, INPUT);
    pinMode(_echoPinNumber, OUTPUT);
}

HCSR04UltrasonicDistanceSensor::HCSR04UltrasonicDistanceSensor(
    byte triggerPinNumber,
    byte echoPinNumber)
{
    _triggerPinNumber = triggerPinNumber;
    _echoPinNumber = echoPinNumber;
    _receptionDelayInMicroseconds = 10;

    pinMode(_triggerPinNumber, INPUT);
    pinMode(_echoPinNumber, OUTPUT);
}

unsigned int HCSR04UltrasonicDistanceSensor::getReceptionDelayInMicroseconds()
{
    return _receptionDelayInMicroseconds;
}

byte HCSR04UltrasonicDistanceSensor::getTriggerPinNumber()
{
    return _triggerPinNumber;
}

byte HCSR04UltrasonicDistanceSensor::getEchoPinNumber()
{
    return _echoPinNumber;
}

unsigned int HCSR04UltrasonicDistanceSensor::getAnalogInput()
{
    digitalWrite(_echoPinNumber, HIGH);
    delayMicroseconds(_receptionDelayInMicroseconds);
    digitalWrite(_echoPinNumber, LOW);
    return pulseIn(_triggerPinNumber, HIGH);
}
