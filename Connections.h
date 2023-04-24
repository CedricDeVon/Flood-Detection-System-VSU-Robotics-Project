#include <Arduino.h>
#ifndef Connections_h
#define Connections_h

class Connections
{
    public:
        Connections(unsigned int);
        unsigned int getSerialBandwidth();

    private:
        unsigned int _serialBandwidth;
};

#endif
