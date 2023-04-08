#include <Arduino.h>
#include "FloodLevelHandler.h"

char* FloodLevelHandler::getStringEquivalent(byte index)
{
    if (_isIndexInvalid(index))
    {
        return NULL;
    }
    else
    {
        return _stringEquivalents[index];
    }
}

bool FloodLevelHandler::_isIndexInvalid(byte index)
{
    return index < 0 || index >= sizeof(_stringEquivalents) / sizeof(_stringEquivalents[0]);
}
