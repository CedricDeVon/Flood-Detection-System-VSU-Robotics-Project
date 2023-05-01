#include <Arduino.h>

#ifndef LightEmittingDiode_h
#define LightEmittingDiode_h

class LightEmittingDiode
{
    public:
        LightEmittingDiode(byte, unsigned long);
        LightEmittingDiode(byte);
        byte getPinNumber();
        bool getCurrentState();
        unsigned long getDurationInMilliseconds();
        void turnOn();
        void turnOff();
        void blink();
        void blink(unsigned long);

    private:
        byte _pinNumber;
        bool _currentState;
        unsigned long _durationInMilliseconds;
        unsigned long _timestampInMilliseconds;
        bool _isTheRightTimeToChangeState(unsigned long, unsigned long);
        void _changeCurrentState();
};

#endif
