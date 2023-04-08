#include <Arduino.h>
#ifndef WaterSensor_h
#define WaterSensor_h

class WaterSensor
{
    public:
        WaterSensor(byte, byte);
        byte getPowerPinNumber();
        byte getInputPinNumber();
        unsigned int getInputValue();
        void turnSensorOn();
        void turnSensorOff();

    private:
        byte _powerPinNumber;
        byte _inputPinNumber;
};

#endif
