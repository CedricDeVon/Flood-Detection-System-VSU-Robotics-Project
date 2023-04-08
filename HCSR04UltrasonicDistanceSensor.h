#include <Arduino.h>
#ifndef HCSR04UltrasonicDistanceSensor_h
#define HCSR04UltrasonicDistanceSensor_h

class HCSR04UltrasonicDistanceSensor
{
    public:
        HCSR04UltrasonicDistanceSensor(byte, byte);
        HCSR04UltrasonicDistanceSensor(byte, byte, unsigned int);
        unsigned int getReceptionDelayInMicroseconds();
        byte getInputPinNumber();
        byte getOutputPinNumber();
        unsigned int getAnalogInput();
       
    private:
        unsigned int _receptionDelayInMicroseconds;
        byte _inputPinNumber;
        byte _outputPinNumber;
};

#endif
