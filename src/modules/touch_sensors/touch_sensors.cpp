#include <ArduinoBLE.h>

#include "touch_sensors.hpp"
#include "../../constants/constants.hpp"

bool touchSensorsEnabled;
BLEService touchSensorService("touch-sensors-service");
BLEBoolCharacteristic touchSensorEnabledCharacteristic("touch-sensors-enabled", BLERead | BLEWrite);


void onTouchSensorsChange(BLEDevice central, BLECharacteristic characteristic);

void setupTouchSensors()
{
    pinMode(TOUCH_SENSORS_TOGGLE_PIN, OUTPUT);
}

void setupTouchSensorsBLE()
{
    BLE.setAdvertisedService(touchSensorService);
    touchSensorEnabledCharacteristic.setEventHandler(BLEWritten, onTouchSensorsChange);
    touchSensorService.addCharacteristic(touchSensorEnabledCharacteristic);
    BLE.addService(touchSensorService);
}

void onTouchSensorsChange(BLEDevice central, BLECharacteristic characteristic)
{
    byte enabled;
    characteristic.readValue(enabled);
    touchSensorsEnabled = enabled;
    digitalWrite(TOUCH_SENSORS_TOGGLE_PIN, touchSensorsEnabled);
}