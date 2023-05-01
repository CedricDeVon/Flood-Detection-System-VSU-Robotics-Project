#include <Arduino.h>

#include "FloodLevels.h"

char* FloodLevels::getLevelName(byte index)
{
    return (_isIndexInvalid(index)) ? NULL : _levelNames[index];
}

int FloodLevels::getLevelNameSize(byte index)
{
    return (_isIndexInvalid(index)) ? NULL : _levelNameSizes[index];
}

bool FloodLevels::_isIndexInvalid(byte index)
{
    return index < 0 || index >= sizeof(_levelNames) / sizeof(_levelNames[0]);
}
