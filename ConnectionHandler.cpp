#include <Arduino.h>
#include "ConnectionHandler.h"

ConnectionHandler::ConnectionHandler(unsigned int serialBandwidth)
{
    _serialBandwidth = serialBandwidth;
    Serial.begin(_serialBandwidth);
}

unsigned int ConnectionHandler::getSerialBandwidth()
{
    return _serialBandwidth;
}

