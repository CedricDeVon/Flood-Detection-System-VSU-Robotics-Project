#include "Utilities.h"
#include "DebugLogger.h"
#include "FloodLevelHandler.h"
#include "HCSR04DistanceCalculator.h"
#include "ConnectionHandler.h"

#include "LED.h"
#include "Speaker.h"
#include "HCSR04UltrasonicDistanceSensor.h"
#include "LiquidCrystalDisplay.h"
#include "WaterSensor.h"

Utilities utilities;
DebugLogger debugLogger("Info");
FloodLevelHandler floodLevelHandler;
HCSR04DistanceCalculator hcsr04DistanceCalculator;
ConnectionHandler connectionHandler(9600);

LED led(2, 250);
Speaker speaker(5, 1000, 250);
HCSR04UltrasonicDistanceSensor hcsr04UltrasonicDistanceSensor(4, 3);
LiquidCrystalDisplay liquidCrystalDisplay(12, 11, 10, 9, 8, 7, 1, 16);

void setup() {}

void loop()
{
    unsigned int analogInput = hcsr04UltrasonicDistanceSensor.getAnalogInput();
		unsigned int distanceInCentimeters = hcsr04DistanceCalculator.getIntegerConversion(analogInput, 0);
    char* textInCentimeters = utilities.convert(distanceInCentimeters, 3);
    char* distanceMeasurement = hcsr04DistanceCalculator.getStringEquivalent(0);
    char* floodLevel = floodLevelHandler.getStringEquivalent(distanceInCentimeters / 100);
    liquidCrystalDisplay.displayTextAtCoordinates(textInCentimeters, 0, 0);
    liquidCrystalDisplay.displayTextAtCoordinates(distanceMeasurement, 3, 0);
    liquidCrystalDisplay.displayTextAtCoordinates(" : ", 5, 0);
    liquidCrystalDisplay.displayTextAtCoordinates(floodLevel, 8, 0);
    delete textInCentimeters;

		if (distanceInCentimeters <= 100)
		{
				led.blink();
				speaker.blink();
		}
    else
    {
        led.turnOff();
        speaker.turnOff();
    }
}

