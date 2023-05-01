#include <Arduino.h>
#include <LiquidCrystal.h>

#ifndef LiquidCrystalDisplay_h
#define LiquidCrystalDisplay_h

class LiquidCrystalDisplay
{
    public:
        LiquidCrystalDisplay(byte, byte, byte, byte, byte, byte, byte, byte);
        byte getCommandOrDataSelectPin();
        byte getEnablePin();
        byte getParallelData4Pin();
        byte getParallelData5Pin();
        byte getParallelData6Pin();
        byte getParallelData7Pin();
        byte getMaximumCellRows();
        byte getMaximumCellColumns();
        byte getCurrentCustomCharacterCount();
        byte getMaximumCustomCharacterCount();
        void displayTextAtCoordinates(char[], byte, byte);
        void displayTextAtCoordinates(char[], byte);
        void clearDisplay(byte, byte, byte);
        void clearDisplay(byte, byte);
        void clearDisplay(bool);
        void clearDisplay();
        void addCustomCharacter(byte[]);

    private:
        byte _commandOrDataSelectPin;
        byte _enablePin;
        byte _parallelData4Pin;
        byte _parallelData5Pin;
        byte _parallelData6Pin;
        byte _parallelData7Pin;
        byte _maximumCellRows;
        byte _maximumCellColumns;
        byte _currentCustomCharacterCount;
        byte _maximumCustomCharacterCount;
        LiquidCrystal* _liquidCrystal = nullptr;
};

#endif
