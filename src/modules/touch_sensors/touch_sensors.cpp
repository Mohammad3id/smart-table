#include <Arduino.h>

#include "touch_sensors.hpp"
#include "../../constants/constants.hpp"

bool touchSensorsEnabled;

void setupTouchSensors()
{
    pinMode(TOUCH_SENSORS_TOGGLE_PIN, OUTPUT);
}

void handleTouchSensorCommand(String command)
{
    touchSensorsEnabled = command.endsWith("on");
    digitalWrite(TOUCH_SENSORS_TOGGLE_PIN, touchSensorsEnabled);
}