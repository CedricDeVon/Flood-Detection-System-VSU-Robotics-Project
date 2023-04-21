#include "Utilities.h"
#include "DebugLogger.h"
#include "FloodLevels.h"
#include "HCSR04UltrasonicDistanceCalculator.h"
#include "ConnectionHandler.h"

#include "LED.h"
#include "Speaker.h"
#include "HCSR04UltrasonicDistanceSensor.h"
#include "LiquidCrystalDisplay.h"
#include "WaterSensor.h"

#define SERIAL_BANDWIDTH 9600

#define FIRST_LED_PIN 2
#define FIRST_SPEAKER_PIN 5
#define SPEAKER_TONE_IN_HERTZ 1000
#define LED_SPEAKER_DELAY_IN_MILLISECONDS 250

#define HCSR04_ULTRASONIC_DISTANCE_SENSOR_INPUT_PIN 4
#define HCSR04_ULTRASONIC_DISTANCE_SENSOR_OUTPUT_PIN 3

#define MAXIMUM_DISTANCE_IN_INCHES 10
#define DISTANCE_MEASUREMENT 1 // Inches
#define SAFE_LEVEL_TOLERANCE_IN_INCHES 3
#define LIQUID_CRYSTAL_DISPLAY_DELAY_IN_MILLISECONDS 500
#define SAFE_LEVEL 0
#define DANGER_LEVEL 1

#define COMMAND_OR_DATA_SELECT_PIN 12
#define ENABLE_PIN 11
#define PARALLEL_DATA_4_PIN 10
#define PARALLEL_DATA_5_PIN 9
#define PARALLEL_DATA_6_PIN 8
#define PARALLEL_DATA_7_PIN 7
#define ROW_COUNT 1
#define COLUMN_COUNT 16

Utilities utilities;
FloodLevels floodLevels;
ConnectionHandler connectionHandler(SERIAL_BANDWIDTH);
LED leds[1] = {
    LED(
        FIRST_LED_PIN,
        LED_SPEAKER_DELAY_IN_MILLISECONDS
    )
};
Speaker speakers[1] = {
    Speaker(
        FIRST_SPEAKER_PIN,
        SPEAKER_TONE_IN_HERTZ,
        LED_SPEAKER_DELAY_IN_MILLISECONDS
    )
};
HCSR04UltrasonicDistanceSensor hcsr04UltrasonicDistanceSensor(
    HCSR04_ULTRASONIC_DISTANCE_SENSOR_INPUT_PIN,
    HCSR04_ULTRASONIC_DISTANCE_SENSOR_OUTPUT_PIN
);
HCSR04UltrasonicDistanceCalculator hcsr04UltrasonicDistanceCalculator(
    MAXIMUM_DISTANCE_IN_INCHES,
    DISTANCE_MEASUREMENT
);
LiquidCrystalDisplay liquidCrystalDisplay(
    COMMAND_OR_DATA_SELECT_PIN,
    ENABLE_PIN,
    PARALLEL_DATA_4_PIN,
    PARALLEL_DATA_5_PIN,
    PARALLEL_DATA_6_PIN,
    PARALLEL_DATA_7_PIN,
    ROW_COUNT,
    COLUMN_COUNT
);

void runtime();
void triggerLEDsAndSpeakers(unsigned int);
void displayDistanceToLCD(unsigned int);

void runtime()
{
		unsigned int distance = hcsr04UltrasonicDistanceCalculator.getIntegerConversion(
        hcsr04UltrasonicDistanceSensor.getAnalogInput()
    );
    triggerLEDsAndSpeakers(distance);
    displayDistanceToLCD(distance);
}

void triggerLEDsAndSpeakers(unsigned int distance)
{
		if (distance < SAFE_LEVEL_TOLERANCE_IN_INCHES)
		{
				leds[0].blink();
				speakers[0].blink();
		}
    else
    {
        leds[0].turnOff();
        speakers[0].turnOff();
    }
}

unsigned long timestampInMilliseconds = 0;
void displayDistanceToLCD(unsigned int distance)
{
    unsigned long currentTimeInMillisecondsSinceArduinoInitialization = millis();
    if (
        (currentTimeInMillisecondsSinceArduinoInitialization - timestampInMilliseconds) >= 
        LIQUID_CRYSTAL_DISPLAY_DELAY_IN_MILLISECONDS)
    {
        timestampInMilliseconds = currentTimeInMillisecondsSinceArduinoInitialization;

        char stringDistance[4];
        unsigned int cellRowIndex = 0;
        liquidCrystalDisplay.clearDisplay();
        sprintf(stringDistance, "%d", distance);
        liquidCrystalDisplay.displayTextAtCoordinates(
            stringDistance,
            cellRowIndex
        );
        cellRowIndex += utilities.getDigitSum(distance) + 1;
        liquidCrystalDisplay.displayTextAtCoordinates(
            hcsr04UltrasonicDistanceCalculator.getMeasurementName(),
            cellRowIndex
        );
        cellRowIndex += hcsr04UltrasonicDistanceCalculator.getMeasurementNameSize();
        liquidCrystalDisplay.displayTextAtCoordinates(" : ", cellRowIndex);
        cellRowIndex += 3;
        liquidCrystalDisplay.displayTextAtCoordinates(
            (distance < SAFE_LEVEL_TOLERANCE_IN_INCHES) ?
            floodLevels.getLevelName(SAFE_LEVEL) :
            floodLevels.getLevelName(DANGER_LEVEL),
            cellRowIndex
        );
    }
}
