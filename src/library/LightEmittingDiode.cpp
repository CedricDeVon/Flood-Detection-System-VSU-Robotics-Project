#include <Arduino.h>

#include "LightEmittingDiode.h"

LightEmittingDiode::LightEmittingDiode(byte pinNumber)
{
    _pinNumber = pinNumber;
    _currentState = LOW;
    _timestampInMilliseconds = 0;

    pinMode(_pinNumber, OUTPUT);
}

LightEmittingDiode::LightEmittingDiode(byte pinNumber, unsigned long durationInMilliseconds)
{
    _pinNumber = pinNumber;
    _currentState = LOW;
    _durationInMilliseconds = durationInMilliseconds;
    _timestampInMilliseconds = 0;

    pinMode(_pinNumber, OUTPUT);
}

byte LightEmittingDiode::getPinNumber()
{
    return _pinNumber;
}

bool LightEmittingDiode::getCurrentState()
{
    return _currentState;
}

unsigned long LightEmittingDiode::getDurationInMilliseconds()
{
    return _durationInMilliseconds;
}

void LightEmittingDiode::turnOn()
{
    digitalWrite(_pinNumber, HIGH);
}

void LightEmittingDiode::turnOff()
{
    digitalWrite(_pinNumber, LOW);
}

void LightEmittingDiode::blink()
{
    blink(_durationInMilliseconds);
}

void LightEmittingDiode::blink(unsigned long durationInMilliseconds)
{
    unsigned long currentTimeInMilliseconds = millis();
    if (_isTheRightTimeToChangeState(currentTimeInMilliseconds, durationInMilliseconds))
    {
        _timestampInMilliseconds = currentTimeInMilliseconds;
        _changeCurrentState();
        digitalWrite(_pinNumber, _currentState);
    }
}

bool LightEmittingDiode::_isTheRightTimeToChangeState(
    unsigned long currentTimeInMilliseconds,
    unsigned long durationInMilliseconds)
{
    return (currentTimeInMilliseconds - _timestampInMilliseconds) >= durationInMilliseconds;
}

void LightEmittingDiode::_changeCurrentState()
{
    _currentState = (_currentState == LOW) ? HIGH : LOW;
}


