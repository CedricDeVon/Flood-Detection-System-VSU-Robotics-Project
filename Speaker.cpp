#include <Arduino.h>
#include "Speaker.h"

Speaker::Speaker(byte pinNumber)
{
    _pinNumber = pinNumber;

    pinMode(_pinNumber, OUTPUT);
}

Speaker::Speaker(byte pinNumber, unsigned short toneInHertz)
{
    _pinNumber = pinNumber;
    _toneInHertz = toneInHertz;

    pinMode(_pinNumber, OUTPUT);
}

Speaker::Speaker(byte pinNumber, unsigned short toneInHertz, unsigned int durationInMilliseconds)
{
    _pinNumber = pinNumber;
    _toneInHertz = toneInHertz;
    _durationInMilliseconds = durationInMilliseconds;

    pinMode(_pinNumber, OUTPUT);
}

byte Speaker::getPinNumber()
{
  return _pinNumber;
}

bool Speaker::getCurrentState()
{
  return _currentState;
}

unsigned short Speaker::getToneInHertz()
{
  return _toneInHertz;
}

unsigned int Speaker::getDurationInMilliseconds()
{
  return _durationInMilliseconds;
}

void Speaker::turnOn()
{
    tone(_pinNumber, _toneInHertz);
}

void Speaker::turnOn(unsigned short toneInHertz)
{
    tone(_pinNumber, toneInHertz);
}

void Speaker::turnOff()
{
    noTone(_pinNumber);
}

void Speaker::blink()
{
    blink(_toneInHertz, _durationInMilliseconds);
}

void Speaker::blink(unsigned short toneInHertz)
{
    blink(toneInHertz, _durationInMilliseconds);
}

void Speaker::blink(unsigned short toneInHertz, unsigned int durationInMilliseconds)
{
    unsigned long currentTimeInMilliseconds = millis();
    if (_isTheRightTimeToChangeState(currentTimeInMilliseconds, durationInMilliseconds))
    {
        _timestampInMilliseconds = currentTimeInMilliseconds;
        _changeCurrentState();
        _decideWetherToTurnOnOrOff();
    }
}

bool Speaker::_isTheRightTimeToChangeState(
    unsigned long currentTimeInMilliseconds,
    unsigned int durationInMilliseconds)
{
    return (currentTimeInMilliseconds - _timestampInMilliseconds) >= durationInMilliseconds;
}

void Speaker::_changeCurrentState()
{
    _currentState = (_currentState == LOW) ? HIGH : LOW;
}

void Speaker::_decideWetherToTurnOnOrOff()
{
    if (_currentState == HIGH)
    {
        turnOn(_toneInHertz);
    }
    else if (_currentState == LOW)
    {
        turnOff();
    }
}

