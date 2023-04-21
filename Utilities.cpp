#include <Arduino.h>
#include "Utilities.h"

unsigned int Utilities::getDigitSum(int number)
{
    unsigned int count = 0;
    while (number > 0)
    {
        number /= 10;
        count += 1;
    }
    return count;
}

	