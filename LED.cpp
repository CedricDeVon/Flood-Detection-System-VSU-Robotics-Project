#include <Arduino.h>
#include "LED.h"

LED::LED(byte pinNumber)
{
    _pinNumber = pinNumber;
    _currentState = LOW;
    _timestampInMilliseconds = 0;

    pinMode(_pinNumber, OUTPUT);
}

LED::LED(byte pinNumber, unsigned long durationInMilliseconds)
{
    _pinNumber = pinNumber;
    _currentState = LOW;
    _durationInMilliseconds = durationInMilliseconds;
    _timestampInMilliseconds = 0;

    pinMode(_pinNumber, OUTPUT);
}

byte LED::getPinNumber()
{
    return _pinNumber;
}

bool LED::getCurrentState()
{
    return _currentState;
}

unsigned long LED::getDurationInMilliseconds()
{
    return _durationInMilliseconds;
}

void LED::turnOn()
{
    digitalWrite(_pinNumber, HIGH);
}

void LED::turnOff()
{
    digitalWrite(_pinNumber, LOW);
}

void LED::blink()
{
    blink(_durationInMilliseconds);
}

void LED::blink(unsigned long durationInMilliseconds)
{
    unsigned long currentTimeInMilliseconds = millis();
    if (_isTheRightTimeToChangeState(currentTimeInMilliseconds, durationInMilliseconds))
    {
        _timestampInMilliseconds = currentTimeInMilliseconds;
        _changeCurrentState();
        digitalWrite(_pinNumber, _currentState);
    }
}

bool LED::_isTheRightTimeToChangeState(
    unsigned long currentTimeInMilliseconds,
    unsigned long durationInMilliseconds)
{
    return (currentTimeInMilliseconds - _timestampInMilliseconds) >= durationInMilliseconds;
}

void LED::_changeCurrentState()
{
    _currentState = (_currentState == LOW) ? HIGH : LOW;
}


