#include <Arduino.h>
#ifndef LED_h
#define LED_h

class LED
{
    public:
        LED(byte);
        LED(byte, unsigned int);
        byte getPinNumber();
        bool getCurrentState();
        unsigned int getDurationInMilliseconds();
        void turnOn();
        void turnOff();
        void blink();
        void blink(unsigned int);

    private:
        byte _pinNumber;
        bool _currentState;
        unsigned int _durationInMilliseconds;
        unsigned long _timestampInMilliseconds;
        bool _isTheRightTimeToChangeState(unsigned long, unsigned int);
        void _changeCurrentState();
};

#endif
