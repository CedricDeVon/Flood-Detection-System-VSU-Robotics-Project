#include <Arduino.h>

#include "library/Utilities.h"
#include "library/Connections.h"
#include "library/HCSR04UltrasonicDistanceCalculator.h"
#include "library/HCSR04UltrasonicDistanceSensor.h"
#include "library/FloodLevels.h"
#include "library/LightEmittingDiode.h"
#include "library/Buzzer.h"
#include "library/LiquidCrystalDisplay.h"

#ifndef FloodDetectionSystemApplication_h
#define FloodDetectionSystemApplication_h

const Utilities utilities;

const unsigned int SERIAL_BANDWIDTH = 9600;
const Connections connections(SERIAL_BANDWIDTH);

const byte MEASUREMENT_IN_INCHES = 1; 
const unsigned int SAFE_LEVEL_TOLERANCE_IN_INCHES = 12;
const HCSR04UltrasonicDistanceCalculator hcsr04UltrasonicDistanceCalculator(
    MEASUREMENT_IN_INCHES);

bool hasCrossedTheSafeDistanceThreshold(unsigned int distance)
{
    return distance <= SAFE_LEVEL_TOLERANCE_IN_INCHES;
}

unsigned int currentNotWithinSafeDistanceCount = 0;
unsigned int maximumNotWithinSafeDistanceCount = 5;
bool isDistanceWithinPendingLevel(unsigned int distance)
{
    return hasCrossedTheSafeDistanceThreshold(distance) &&
        currentNotWithinSafeDistanceCount < maximumNotWithinSafeDistanceCount;
}

bool isDistanceWithinDangerLevel(unsigned int distance)
{
    return hasCrossedTheSafeDistanceThreshold(distance) &&
        currentNotWithinSafeDistanceCount >= maximumNotWithinSafeDistanceCount;
}

const byte HCSR04_ULTRASONIC_DISTANCE_SENSOR_TRIGGER_PIN = 4;
const byte HCSR04_ULTRASONIC_DISTANCE_SENSOR_ECHO_PIN = 5;
const HCSR04UltrasonicDistanceSensor hcsr04UltrasonicDistanceSensor(
    HCSR04_ULTRASONIC_DISTANCE_SENSOR_TRIGGER_PIN,
    HCSR04_ULTRASONIC_DISTANCE_SENSOR_ECHO_PIN);

unsigned int getHcsr04UltrasonicDistanceSensorDistance()
{
    return hcsr04UltrasonicDistanceCalculator.getIntegerConversion(
        hcsr04UltrasonicDistanceSensor.getAnalogInput());
}

const FloodLevels floodLevels;
const byte DANGER_LEVEL = 0;
const byte PENDING_LEVEL = 1;
const byte SAFE_LEVEL = 2;
byte getCurrentFloodLevel(unsigned int distance)
{
    if (isDistanceWithinPendingLevel(distance))
    {
        return PENDING_LEVEL;
    }
    else if (isDistanceWithinDangerLevel(distance))
    {
        return DANGER_LEVEL;
    }
    else
    {
        return SAFE_LEVEL;
    }
}

const byte FIRST_LIGHT_EMITTING_DIODE_PIN = 2;
const unsigned long OUTPUT_REFRESH_DELAY_IN_MILLISECONDS = 500;
const LightEmittingDiode LightEmittingDiodes[1] = {
    LightEmittingDiode(
        FIRST_LIGHT_EMITTING_DIODE_PIN,
        OUTPUT_REFRESH_DELAY_IN_MILLISECONDS)};

const byte FIRST_BUZZER_PIN = 13;
const unsigned short BUZZER_TONE_IN_HERTZ = 1000;
const Buzzer Buzzers[1] = {
    Buzzer(
        FIRST_BUZZER_PIN,
        BUZZER_TONE_IN_HERTZ,
        OUTPUT_REFRESH_DELAY_IN_MILLISECONDS)};

void triggerLightEmittingDiodesAndBuzzers(unsigned int distance)
{
    if (hasCrossedTheSafeDistanceThreshold(distance) &&
        currentNotWithinSafeDistanceCount >= maximumNotWithinSafeDistanceCount)
    {
        LightEmittingDiodes[0].blink();
        Buzzers[0].blink();
    } else {
        LightEmittingDiodes[0].turnOff();
        Buzzers[0].turnOff();
    }
}

const byte COMMAND_OR_DATA_SELECT_PIN = 12;
const byte ENABLE_PIN = 11;
const byte PARALLEL_DATA_4_PIN = 10;
const byte PARALLEL_DATA_5_PIN = 9;
const byte PARALLEL_DATA_6_PIN = 8;
const byte PARALLEL_DATA_7_PIN = 7;
const byte ROW_COUNT = 1;
const byte COLUMN_COUNT  = 16;
const LiquidCrystalDisplay liquidCrystalDisplay(
    COMMAND_OR_DATA_SELECT_PIN,
    ENABLE_PIN,
    PARALLEL_DATA_4_PIN,
    PARALLEL_DATA_5_PIN,
    PARALLEL_DATA_6_PIN,
    PARALLEL_DATA_7_PIN,
    ROW_COUNT,
    COLUMN_COUNT);

unsigned long lcdTimestampInMilliseconds = 0;
const unsigned long LOOP_DELAY_IN_MILLISECONDS = 1000;
bool hasLoopDelayBeenReached(
    unsigned long newTimestampInMilliseconds,
    unsigned int oldTimestampInMilliseconds)
{
    return (newTimestampInMilliseconds - oldTimestampInMilliseconds) >= 
        LOOP_DELAY_IN_MILLISECONDS;
}

bool hasOutputRefreshDelayBeenReached(
    unsigned long newTimestampInMilliseconds,
    unsigned int oldTimestampInMilliseconds)
{
    return (newTimestampInMilliseconds - oldTimestampInMilliseconds) >= 
        OUTPUT_REFRESH_DELAY_IN_MILLISECONDS;
}

unsigned long loopTimestampInMilliseconds = 0;
unsigned int handleCurrentNotWithinSafeDistanceCount(
    unsigned long currentTimeSinceArduinoInitializationInMilliseconds, 
    unsigned int distance)
{
    if (hasLoopDelayBeenReached(
        currentTimeSinceArduinoInitializationInMilliseconds,
        loopTimestampInMilliseconds) && isDistanceWithinPendingLevel(distance))
    {
        loopTimestampInMilliseconds = currentTimeSinceArduinoInitializationInMilliseconds;
        currentNotWithinSafeDistanceCount += 1;
    } else if (hasLoopDelayBeenReached(
        currentTimeSinceArduinoInitializationInMilliseconds,
        loopTimestampInMilliseconds) && isDistanceWithinDangerLevel(distance))
    {
        loopTimestampInMilliseconds = currentTimeSinceArduinoInitializationInMilliseconds;
        currentNotWithinSafeDistanceCount = maximumNotWithinSafeDistanceCount;
    } else if (hasLoopDelayBeenReached(
        currentTimeSinceArduinoInitializationInMilliseconds, loopTimestampInMilliseconds) &&
        !hasCrossedTheSafeDistanceThreshold(distance))
    {
        loopTimestampInMilliseconds = currentTimeSinceArduinoInitializationInMilliseconds;
        currentNotWithinSafeDistanceCount = 0;
    }
}

unsigned int savedDistance = 0;
void displayDistanceToLCD(unsigned int distance) {
    unsigned long currentTimeSinceArduinoInitializationInMilliseconds = millis();
    if (hasOutputRefreshDelayBeenReached(
        currentTimeSinceArduinoInitializationInMilliseconds,
        lcdTimestampInMilliseconds))
    {
        lcdTimestampInMilliseconds = currentTimeSinceArduinoInitializationInMilliseconds;

        savedDistance = distance;
        liquidCrystalDisplay.clearDisplay(savedDistance != distance);

        byte cellColumnIndex = 0;
        char characterStringDistance[4];
        sprintf(characterStringDistance, "%d", distance);
        liquidCrystalDisplay.displayTextAtCoordinates(
            characterStringDistance, cellColumnIndex);
        liquidCrystalDisplay.displayTextAtCoordinates(
            hcsr04UltrasonicDistanceCalculator.getMeasurementName(),
            cellColumnIndex += utilities.getDigitSum(distance));
        liquidCrystalDisplay.displayTextAtCoordinates(
            " : ", cellColumnIndex += hcsr04UltrasonicDistanceCalculator.getMeasurementNameSize());
        byte currentFloodLevel = getCurrentFloodLevel(distance);

        liquidCrystalDisplay.displayTextAtCoordinates(
            floodLevels.getLevelName(currentFloodLevel),
            cellColumnIndex += 3);
        liquidCrystalDisplay.clearDisplay(
            0, cellColumnIndex += floodLevels.getLevelNameSize(currentFloodLevel));
    }
}

void runFloodDetectionSystemApplication() {
    unsigned int distance = getHcsr04UltrasonicDistanceSensorDistance();
    unsigned long currentTimeSinceArduinoInitializationInMilliseconds = millis();
    handleCurrentNotWithinSafeDistanceCount(
        currentTimeSinceArduinoInitializationInMilliseconds,
        distance);
    triggerLightEmittingDiodesAndBuzzers(distance);
    displayDistanceToLCD(distance);
}

#endif
