#include <ArduinoBLE.h>
#include <FastLED.h>

#include "hexagon_constants.hpp"

#include "../utils/binary_string.hpp"

uint32_t hexagonPowers;
BLEService hexagonsPowerService("hexagons-power-service");
BLEBoolCharacteristic* hexagonsPowerCharacteristic[HEXAGONS_COUNT];


void onHexagonsPowerChange(BLEDevice central, BLECharacteristic characteristic);
void switchHexagonPower(int hexagonIndex, bool power);

void setupHexagonsPowerBLE()
{
    BLE.setAdvertisedService(hexagonsPowerService);
    for (int i = 0; i < HEXAGONS_COUNT; i++)
    {
        auto characteristic = BLEBoolCharacteristic(hexagonUUIDs[i], BLERead | BLEWrite);
        characteristic.setEventHandler(BLEWritten, onHexagonsPowerChange);
        hexagonsPowerService.addCharacteristic(characteristic);
        hexagonsPowerCharacteristic[i] = &characteristic;
    }
    BLE.addService(hexagonsPowerService);
}


void onHexagonsPowerChange(BLEDevice central, BLECharacteristic characteristic)
{
    auto index = atoi(&characteristic.uuid()[8]);
    byte power;
    characteristic.readValue(power);
    switchHexagonPower(index, power);
}

void switchHexagonPower(int hexagonIndex, bool power)
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

    Serial.print("Hexagon ");
    Serial.print(hexagonIndex);
    if (power)
    {
        Serial.println(": ON");
    }
    else
    {
        Serial.println(": OFF");
    }

    Serial.print("Current Power: ");
    Serial.println(binaryString(hexagonPowers, 24));
}