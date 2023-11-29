#include <FastLED.h>
#include <ReactESP.h>

#include "BluetoothA2DP.h"
#include "BluetoothSerial.h"

#include "../constants/constants.hpp"
#include "../modules/color/color.hpp"
#include "../modules/toggle/toggle.hpp"
#include "../modules/touch_sensors/touch_sensors.hpp"
#include "../modules/modes/modes.hpp"
#include "../async/async.hpp"


void setupTable()
{
    setupColor();
    setupToggle();
    setupTouchSensors();
    setupModes();
}

BluetoothSerial SerialBT;
BluetoothA2DPSink a2dp_sink;
String message = "";
void executeCommand(String command);

void setupBluetooth()
{
    a2dp_sink.start(TABLE_NAME);
    SerialBT.begin(TABLE_NAME);

    async.onRepeat(
        0,
        []() {
            if (SerialBT.available()) {
                char chr = SerialBT.read();
                if (chr != '\n') {
                    message += String(chr);
                }
                else {
                    executeCommand(String(message));
                    message = "";
                }
            }
        }
    );
}


void executeCommand(String command) {
    command.trim();
    if (command.startsWith(TOGGLE_COMMAND))
    {
        handleToggleCommand(command);
        Serial.print("Toggle Command: ");
    }
    else if (command.startsWith(COLOR_COMMAND))
    {
        handleColorCommand(command);
        Serial.print("Color Command: ");
    }
    else if (command.startsWith(MODE_COMMAND))
    {
        handleModeCommand(command);
        Serial.print("Mode Command: ");
    }
    else if (command.startsWith(TOUCH_SENSOR_COMMAND))
    {
        handleTouchSensorCommand(command);
        Serial.print("Touch Sensor Command: ");
    }
    Serial.println(command);
    Serial.println();
}