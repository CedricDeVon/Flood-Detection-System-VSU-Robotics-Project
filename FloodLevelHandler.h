#include <Arduino.h>
#ifndef FloodLevelHandler_h
#define FloodLevelHandler_h

class FloodLevelHandler
{
    public:
        char* getStringEquivalent(byte);

    private:
        const char _stringEquivalents[4][16] = 
        {
            "AAAAAAAA",
            "BBBBBBBB",
            "CCCCCCCC",
            "DDDDDDDD"
        };
        bool _isIndexInvalid(byte);
};

#endif
