#include <Arduino.h>
#ifndef LED_h
#define LED_h

class LED
{
    public:
        LED(byte);
        LED(byte, unsigned long);
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
