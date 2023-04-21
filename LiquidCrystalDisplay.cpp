#include <Arduino.h>
#include <LiquidCrystal.h>
#include "LiquidCrystalDisplay.h"

LiquidCrystalDisplay::LiquidCrystalDisplay(
		byte commandOrDataSelectPin,
		byte enablePin,
		byte parallelData4Pin,
		byte parallelData5Pin,
		byte parallelData6Pin,
		byte parallelData7Pin,
		byte maximumCellRows,
        byte maximumCellColumns)
{
    _commandOrDataSelectPin = commandOrDataSelectPin;
    _enablePin = enablePin;
    _parallelData4Pin = parallelData4Pin;
    _parallelData5Pin = parallelData5Pin;
    _parallelData6Pin = parallelData6Pin;
    _parallelData7Pin = parallelData7Pin;
    _maximumCellRows = maximumCellRows;
    _maximumCellColumns = maximumCellColumns;
    _currentCustomCharacterCount = 0;
    _maximumCustomCharacterCount = 7;
    _liquidCrystal = new LiquidCrystal(
        _commandOrDataSelectPin,
        _enablePin,
        _parallelData4Pin,
        _parallelData5Pin,
        _parallelData6Pin,
        _parallelData7Pin);
    _liquidCrystal->begin(_maximumCellColumns, _maximumCellRows);
}

byte LiquidCrystalDisplay::getCommandOrDataSelectPin()
{
    return _commandOrDataSelectPin;
}

byte LiquidCrystalDisplay::getEnablePin()
{
    return _enablePin;
}

byte LiquidCrystalDisplay::getParallelData4Pin()
{
    return _parallelData4Pin;
}

byte LiquidCrystalDisplay::getParallelData5Pin()
{
    return _parallelData5Pin;
}

byte LiquidCrystalDisplay::getParallelData6Pin()
{
    return _parallelData6Pin;
}

byte LiquidCrystalDisplay::getParallelData7Pin()
{
    return _parallelData7Pin;
}

byte LiquidCrystalDisplay::getMaximumCellRows()
{
    return _maximumCellRows;
}

byte LiquidCrystalDisplay::getMaximumCellColumns()
{
    return _maximumCellColumns;
}

byte LiquidCrystalDisplay::getCurrentCustomCharacterCount()
{
    return _currentCustomCharacterCount;
}

byte LiquidCrystalDisplay::getMaximumCustomCharacterCount()
{
    return _maximumCustomCharacterCount;
}

void LiquidCrystalDisplay::displayTextAtCoordinates(char text[], byte rowDisplayCoordinate, byte columnDisplayCoordinate)
{
    _liquidCrystal->setCursor(columnDisplayCoordinate, rowDisplayCoordinate);
    _liquidCrystal->write(text);
}

void LiquidCrystalDisplay::displayTextAtCoordinates(char text[], byte columnDisplayCoordinate)
{
    displayTextAtCoordinates(text, columnDisplayCoordinate, 0);
}

void LiquidCrystalDisplay::clearDisplay()
{
    _liquidCrystal->clear();
}

void LiquidCrystalDisplay::addCustomCharacter(byte customCharacter[])
{
    if (_currentCustomCharacterCount < _maximumCustomCharacterCount)
    {
        _liquidCrystal->createChar(_currentCustomCharacterCount, customCharacter);
        _currentCustomCharacterCount += 1;
    }
}