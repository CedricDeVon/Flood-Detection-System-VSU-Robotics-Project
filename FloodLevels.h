#include <Arduino.h>
#ifndef FloodLevels_h
#define FloodLevels_h

class FloodLevels
{
    public:
        char* getLevelName(byte);
        int getLevelNameSize(byte);

    private:
        const char _levelNames[2][16] = 
        {
            "Danger",
            "Safe"
        };
        const int _levelNameSizes[2] =
        {
            6,
            4
        };
        bool _isIndexInvalid(byte);
};

#endif
