#include <Arduino.h>

#include "Buzzer.h"

Buzzer::Buzzer(byte pinNumber, unsigned short toneInHertz, unsigned long durationInMilliseconds)
{
    _pinNumber = pinNumber;
    _toneInHertz = toneInHertz;
    _durationInMilliseconds = durationInMilliseconds;

    pinMode(_pinNumber, OUTPUT);
}

Buzzer::Buzzer(byte pinNumber, unsigned short toneInHertz)
{
    _pinNumber = pinNumber;
    _toneInHertz = toneInHertz;

    pinMode(_pinNumber, OUTPUT);
}

Buzzer::Buzzer(byte pinNumber)
{
    _pinNumber = pinNumber;

    pinMode(_pinNumber, OUTPUT);
}

byte Buzzer::getPinNumber()
{
    return _pinNumber;
}

bool Buzzer::getCurrentState()
{
    return _currentState;
}

unsigned short Buzzer::getToneInHertz()
{
    return _toneInHertz;
}

unsigned long Buzzer::getDurationInMilliseconds()
{
    return _durationInMilliseconds;
}

void Buzzer::turnOn()
{
    tone(_pinNumber, _toneInHertz);
}

void Buzzer::turnOn(unsigned short toneInHertz)
{
    tone(_pinNumber, toneInHertz);
}

void Buzzer::turnOff()
{
    noTone(_pinNumber);
}

void Buzzer::blink()
{
    blink(_toneInHertz, _durationInMilliseconds);
}

void Buzzer::blink(unsigned short toneInHertz)
{
    blink(toneInHertz, _durationInMilliseconds);
}

void Buzzer::blink(unsigned short toneInHertz, unsigned long durationInMilliseconds)
{
    unsigned long currentTimeInMilliseconds = millis();
    if (_isTheRightTimeToChangeState(currentTimeInMilliseconds, durationInMilliseconds))
    {
        _timestampInMilliseconds = currentTimeInMilliseconds;
        _changeCurrentState();
        _decideWetherToTurnOnOrOff();
    }
}

bool Buzzer::_isTheRightTimeToChangeState(
    unsigned long currentTimeInMilliseconds,
    unsigned long durationInMilliseconds)
{
    return (currentTimeInMilliseconds - _timestampInMilliseconds) >= durationInMilliseconds;
}

void Buzzer::_changeCurrentState()
{
    _currentState = (_currentState == LOW) ? HIGH : LOW;
}

void Buzzer::_decideWetherToTurnOnOrOff()
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

