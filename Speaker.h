#include <Arduino.h>
#ifndef Speaker_h
#define Speaker_h

class Speaker
{
    public:
        Speaker(byte);
        Speaker(byte, unsigned short);
        Speaker(byte, unsigned short, unsigned int);
        byte getPinNumber();
        bool getCurrentState();
        unsigned short getToneInHertz();
        unsigned int getDurationInMilliseconds();
        void turnOn();
        void turnOn(unsigned short);
        void turnOff();
        void blink();
        void blink(unsigned short);
        void blink(unsigned short, unsigned int);

    private:
        byte _pinNumber;
        bool _currentState;
        unsigned short _toneInHertz;
        unsigned int _durationInMilliseconds;
        unsigned long _timestampInMilliseconds;
        bool _isTheRightTimeToChangeState(unsigned long, unsigned int);
        void _changeCurrentState();
        void _decideWetherToTurnOnOrOff();
};

#endif
