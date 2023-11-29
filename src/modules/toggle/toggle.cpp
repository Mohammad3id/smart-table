#include <ArduinoBLE.h>
#include <FastLED.h>

#include "toggle.hpp"
#include "../../constants/constants.hpp"
#include "../../utils/utils.hpp"

uint32_t hexagonPowers;
BLEService toggleService("toggle-service");
BLEBoolCharacteristic* toggleCharacteristics[HEXAGONS_COUNT];


void onToggleChange(BLEDevice central, BLECharacteristic characteristic);

void setupToggle()
{
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
}

void setupToggleBLE()
{
    BLE.setAdvertisedService(toggleService);
    for (int i = 0; i < HEXAGONS_COUNT; i++)
    {
        auto characteristic = BLEBoolCharacteristic(hexagonUUIDs[i], BLERead | BLEWrite);
        characteristic.setEventHandler(BLEWritten, onToggleChange);
        toggleService.addCharacteristic(characteristic);
        toggleCharacteristics[i] = &characteristic;
    }
    BLE.addService(toggleService);
}


void onToggleChange(BLEDevice central, BLECharacteristic characteristic)
{
    auto index = atoi(&characteristic.uuid()[8]);
    byte power;
    characteristic.readValue(power);
    toggleHexagon(index, power);
}

void toggleHexagon(int hexagonIndex, bool power)
{
    digitalWrite(LATCH_PIN, LOW);

    if (power)
    {
        hexagonPowers = hexagonPowers | (1 << hexagonIndex);
    }
    else
    {
        hexagonPowers = hexagonPowers & ~(1 << hexagonIndex);
    }

    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, hexagonPowers);

    digitalWrite(LATCH_PIN, HIGH);

    // Serial.print("Hexagon ");
    // Serial.print(hexagonIndex);
    // if (power)
    // {
    //     Serial.println(": ON");
    // }
    // else
    // {
    //     Serial.println(": OFF");
    // }

    // Serial.print("Current Power: ");
    // Serial.println(binaryString(hexagonPowers, HEXAGONS_COUNT));
}