#include <ReactESP.h>

#include "ArduinoBLE.h"
#include "modes.hpp"
#include "../../async/async.hpp"
#include "../color/color.hpp"
#include "../../utils/utils.hpp"

TableModes currentMode = Normal;
BLEService modesService("modes-service");
BLEByteCharacteristic currentModeCharacteristics("current-mode", BLERead | BLEWrite);

reactesp::Reaction* currentLoop;


void onCurrentModeChange(BLEDevice central, BLECharacteristic characteristic);
void enableColorfulMode();
void enableNormalMode();

void setupModes()
{
    // In case of any future setups
}

void setupModesBLE()
{
    BLE.setAdvertisedService(modesService);
    currentModeCharacteristics.setEventHandler(BLEWritten, onCurrentModeChange);
    modesService.addCharacteristic(currentModeCharacteristics);
    BLE.addService(modesService);
}


void onCurrentModeChange(BLEDevice central, BLECharacteristic characteristic)
{
    byte newMode;
    characteristic.readValue(newMode);

    switch (newMode)
    {
    case TableModes::Colorful:
        currentMode = Colorful;
        Serial.println("Colorful");
        enableColorfulMode();
        break;

    case TableModes::Music:
        currentMode = Music;
        Serial.println("Music");
        break;

    default:
        currentMode = Normal;
        Serial.println("Normal");
        enableNormalMode();
        break;
    }
}

void enableNormalMode()
{
    if (currentLoop)
    {
        currentLoop->remove();
    }
    setHexagonsColor(getCurrentColor());
}

void enableColorfulMode()
{
    if (currentLoop)
    {
        currentLoop->remove();
    }
    
    static CRGB startColor;
    static CRGB endColor;
    static int i;
    static const int steps = 20;

    i = 0;
    startColor = getCurrentColor();
    endColor = getRandomColor();

    currentLoop = async.onRepeat(
        50,
        []() {
            setHexagonsColor(interpolateColor(startColor, endColor, i, steps));
            i = (i + 1) % (steps + 1);
            if (i == 0)
            {
                startColor = endColor;
                endColor = getRandomColor();
            }
        }
    );
    
}
