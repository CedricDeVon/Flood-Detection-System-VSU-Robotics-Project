#include <Arduino.h>

#ifndef HCSR04UltrasonicDistanceCalculator_h
#define HCSR04UltrasonicDistanceCalculator_h

class HCSR04UltrasonicDistanceCalculator
{
    public:
        HCSR04UltrasonicDistanceCalculator(unsigned int, byte);
        HCSR04UltrasonicDistanceCalculator(unsigned int);
        HCSR04UltrasonicDistanceCalculator(byte);
        unsigned int getIntegerConversion(unsigned int);
        unsigned int getMaximumDistance();
        byte getMeasurementIndex();
        char *getMeasurementName();
        int getMeasurementNameSize();

    private:
        unsigned int _maximumDistance;
        byte _measurementIndex;
        char _measurementNames[2][16] = {"cm", "in"};
        int _measurementNameSizes[2] = {2, 2};
        double _measurementValues[2] = {29.1, 148};
        bool _isIndexInvalid(byte);
};

#endif


