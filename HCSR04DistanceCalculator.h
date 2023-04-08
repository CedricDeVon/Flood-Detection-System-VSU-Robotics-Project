#include <Arduino.h>
#ifndef HCSR04DistanceCalculator_h
#define HCSR04DistanceCalculator_h

class HCSR04DistanceCalculator
{
    public:
        unsigned int getIntegerConversion(unsigned int);
        unsigned int getIntegerConversion(unsigned int, byte);
        char *getStringEquivalent(byte);

    private:
        char _stringEquivalents[2][16] = {"cm", "in"};
        unsigned short _valueEquivalents[2] = {58, 148};
        bool _isIndexInvalid(byte);
};

#endif


