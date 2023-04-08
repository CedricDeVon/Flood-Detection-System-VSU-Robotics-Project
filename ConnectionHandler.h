#include <Arduino.h>
#ifndef ConnectionHandler_h
#define ConnectionHandler_h

class ConnectionHandler
{
    public:
        ConnectionHandler(unsigned int);
        unsigned int getSerialBandwidth();

    private:
        unsigned int _serialBandwidth;
};

#endif
