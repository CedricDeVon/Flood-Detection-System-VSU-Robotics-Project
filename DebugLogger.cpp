#include <Arduino.h>
#include "DebugLogger.h"

DebugLogger::DebugLogger(char* type)
{
    _type = type;
    _isAllowedToLog = true;
}

char* DebugLogger::getType()
{
    return _type;
}

bool DebugLogger::getIsAllowedToLog()
{
    return _isAllowedToLog;
}

void DebugLogger::startLogging()
{
    _isAllowedToLog = true;
}

void DebugLogger::stopLogging()
{
    _isAllowedToLog = false;
}

void DebugLogger::logText(char* text)
{
    if (!_isAllowedToLog)
    {
        return;
    }

    Serial.print("> ");
    Serial.print(_type);
    Serial.print(" : ");
    Serial.print(text);
}

void DebugLogger::logTextWithNewLine(char* text)
{
    if (!_isAllowedToLog)
    {
        return;
    }

    Serial.print("> ");
    Serial.print(_type);
    Serial.print(" : ");
    Serial.println(text);
}
