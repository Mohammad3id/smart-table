#include "ArduinoBLE.h"
#include "modes.hpp"

TableModes currentMode = Normal;
BLEService modesService("modes-service");
BLEByteCharacteristic currentModeCharacteristics("current-mode", BLERead | BLEWrite);


void onCurrentModeChange(BLEDevice central, BLECharacteristic characteristic);
void toggleHexagon(int hexagonIndex, bool power);

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
        break;

    case TableModes::Music:
        currentMode = Music;
        Serial.println("Music");
        break;

    default:
        currentMode = Normal;
        Serial.println("Normal");
        break;
    }
}
