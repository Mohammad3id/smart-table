#include <ArduinoBLE.h>
#include <FastLED.h>

#include "../constants/constants.hpp"
#include "../modules/color/color.hpp"
#include "../modules/toggle/toggle.hpp"
#include "../modules/touch_sensors/touch_sensors.hpp"
#include "../modules/modes/modes.hpp"

void setupTable()
{
    setupColor();
    setupToggle();
    setupTouchSensors();
    setupModes();
}

void setupTableBLE()
{
    setupColorBLE();
    setupToggleBLE();
    setupTouchSensorsBLE();
    setupModesBLE();
    BLE.setLocalName(TABLE_BLE_NAME);
    BLE.advertise();
}
