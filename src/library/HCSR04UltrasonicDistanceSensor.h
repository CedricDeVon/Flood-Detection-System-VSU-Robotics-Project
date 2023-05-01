#include <Arduino.h>

#ifndef HCSR04UltrasonicDistanceSensor_h
#define HCSR04UltrasonicDistanceSensor_h

class HCSR04UltrasonicDistanceSensor
{
    public:
        HCSR04UltrasonicDistanceSensor(byte, byte, unsigned int);
        HCSR04UltrasonicDistanceSensor(byte, byte);
        unsigned int getReceptionDelayInMicroseconds();
        byte getTriggerPinNumber();
        byte getEchoPinNumber();
        unsigned int getAnalogInput();
       
    private:
        unsigned int _receptionDelayInMicroseconds;
        byte _triggerPinNumber;
        byte _echoPinNumber;
};

#endif
