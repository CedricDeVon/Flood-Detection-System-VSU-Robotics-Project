#include "Connections.h"
#include "Utilities.h"
#include "FloodLevels.h"

#include "LED.h"
#include "Speaker.h"
#include "HCSR04UltrasonicDistanceCalculator.h"
#include "HCSR04UltrasonicDistanceSensor.h"
#include "LiquidCrystalDisplay.h"

#define SERIAL_BANDWIDTH 9600

#define FIRST_LED_PIN 2
#define FIRST_SPEAKER_PIN 13
#define SPEAKER_TONE_IN_HERTZ 1000

#define HCSR04_ULTRASONIC_DISTANCE_SENSOR_TRIGGER_PIN 4
#define HCSR04_ULTRASONIC_DISTANCE_SENSOR_ECHO_PIN 5

#define MAXIMUM_DISTANCE_IN_INCHES 1000
byte DISTANCE_MEASUREMENT = 1;  // In inches
#define SAFE_LEVEL_TOLERANCE_IN_INCHES 12
#define OUTPUT_REFRESH_DELAY_IN_MILLISECONDS 500
#define DANGER_LEVEL 0
#define PENDING_LEVEL 1
#define SAFE_LEVEL 2

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
Connections connections(SERIAL_BANDWIDTH);
LED leds[1] = {
  LED(
    FIRST_LED_PIN,
    OUTPUT_REFRESH_DELAY_IN_MILLISECONDS)
};

Speaker speakers[1] = {
  Speaker(
    FIRST_SPEAKER_PIN,
    SPEAKER_TONE_IN_HERTZ,
    OUTPUT_REFRESH_DELAY_IN_MILLISECONDS)
};

HCSR04UltrasonicDistanceSensor hcsr04UltrasonicDistanceSensor(
  HCSR04_ULTRASONIC_DISTANCE_SENSOR_TRIGGER_PIN,
  HCSR04_ULTRASONIC_DISTANCE_SENSOR_ECHO_PIN);

HCSR04UltrasonicDistanceCalculator hcsr04UltrasonicDistanceCalculator(
  DISTANCE_MEASUREMENT);

LiquidCrystalDisplay liquidCrystalDisplay(
  COMMAND_OR_DATA_SELECT_PIN,
  ENABLE_PIN,
  PARALLEL_DATA_4_PIN,
  PARALLEL_DATA_5_PIN,
  PARALLEL_DATA_6_PIN,
  PARALLEL_DATA_7_PIN,
  ROW_COUNT,
  COLUMN_COUNT);

unsigned int a = 0;
unsigned int b = 5;

unsigned int getHcsr04UltrasonicDistanceSensorDistance() {
  return hcsr04UltrasonicDistanceCalculator.getIntegerConversion(hcsr04UltrasonicDistanceSensor.getAnalogInput());
}

bool hasCrossedTheSafeDistanceThreshold(unsigned int distance) {
  return distance <= SAFE_LEVEL_TOLERANCE_IN_INCHES;
}

void triggerLEDsAndSpeakers(unsigned int distance) {
  if (hasCrossedTheSafeDistanceThreshold(distance) && a >= b) {
    leds[0].blink();
    speakers[0].blink();
  } else {
    leds[0].turnOff();
    speakers[0].turnOff();
  }
}

unsigned int savedDistance = 0;
unsigned long lcdTimestampInMilliseconds = 0;
bool hasOutputRefreshDelayBeenReached(unsigned long newTimestampInMilliseconds, unsigned int oldTimestampInMilliseconds) {
  return (newTimestampInMilliseconds - oldTimestampInMilliseconds) >= OUTPUT_REFRESH_DELAY_IN_MILLISECONDS;
}

void displayDistanceToLCD(unsigned int distance) {
  unsigned long currentTimeSinceArduinoInitializationInMilliseconds = millis();
  if (hasOutputRefreshDelayBeenReached(currentTimeSinceArduinoInitializationInMilliseconds, lcdTimestampInMilliseconds)) {
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
    byte currentFloodLevel;
    if (hasCrossedTheSafeDistanceThreshold(distance) && a < b)
    {
        currentFloodLevel = PENDING_LEVEL;
    }
    else if (hasCrossedTheSafeDistanceThreshold(distance) && a >= b)
    {
        currentFloodLevel = DANGER_LEVEL;
    }
    else
    {
        currentFloodLevel = SAFE_LEVEL;
    }

    liquidCrystalDisplay.displayTextAtCoordinates(
      floodLevels.getLevelName(currentFloodLevel),
      cellColumnIndex += 3);
    liquidCrystalDisplay.clearDisplay(
      0, cellColumnIndex += floodLevels.getLevelNameSize(currentFloodLevel));
  }
}

void setup() {
}

unsigned long loopTimestampInMilliseconds = 0;
void loop() {
  unsigned int distance = getHcsr04UltrasonicDistanceSensorDistance();
  unsigned long currentTimeSinceArduinoInitializationInMilliseconds = millis();
  if (currentTimeSinceArduinoInitializationInMilliseconds - loopTimestampInMilliseconds >= 1000 && hasCrossedTheSafeDistanceThreshold(distance) && a < b) {
    loopTimestampInMilliseconds = currentTimeSinceArduinoInitializationInMilliseconds;
    a += 1;
  } else if (currentTimeSinceArduinoInitializationInMilliseconds - loopTimestampInMilliseconds >= 1000 && hasCrossedTheSafeDistanceThreshold(distance) && a >= b) {
    loopTimestampInMilliseconds = currentTimeSinceArduinoInitializationInMilliseconds;
    a = b;
  } else if (currentTimeSinceArduinoInitializationInMilliseconds - loopTimestampInMilliseconds >= 1000 && !hasCrossedTheSafeDistanceThreshold(distance)) {
    loopTimestampInMilliseconds = currentTimeSinceArduinoInitializationInMilliseconds;
    a = 0;
  }
  Serial.println(a);

  triggerLEDsAndSpeakers(distance);
  displayDistanceToLCD(distance);
}
