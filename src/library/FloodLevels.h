#include <Arduino.h>

#ifndef FloodLevels_h
#define FloodLevels_h

class FloodLevels
{
    public:
        char* getLevelName(byte);
        int getLevelNameSize(byte);

    private:
        const char _levelNames[3][16] = 
        {
            "Danger",
            "Warning",
            "Safe"
        };
        const int _levelNameSizes[3] =
        {
            6,
            7,
            4
        };
        bool _isIndexInvalid(byte);
};

#endif
