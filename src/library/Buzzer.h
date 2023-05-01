#include <Arduino.h>

#ifndef Buzzer_h
#define Buzzer_h

class Buzzer
{
    public:
        Buzzer(byte, unsigned short, unsigned long);
        Buzzer(byte, unsigned short);
        Buzzer(byte);      
        byte getPinNumber();
        bool getCurrentState();
        unsigned short getToneInHertz();
        unsigned long getDurationInMilliseconds();
        void turnOn();
        void turnOn(unsigned short);
        void turnOff();
        void blink();
        void blink(unsigned short);
        void blink(unsigned short, unsigned long);

    private:
        byte _pinNumber;
        bool _currentState;
        unsigned short _toneInHertz;
        unsigned long _durationInMilliseconds;
        unsigned long _timestampInMilliseconds;
        bool _isTheRightTimeToChangeState(unsigned long, unsigned long);
        void _changeCurrentState();
        void _decideWetherToTurnOnOrOff();
};

#endif
