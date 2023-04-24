#include <Arduino.h>
#include "Connections.h"

Connections::Connections(unsigned int serialBandwidth)
{
    _serialBandwidth = serialBandwidth;
    Serial.begin(_serialBandwidth);
}

unsigned int Connections::getSerialBandwidth()
{
    return _serialBandwidth;
}

