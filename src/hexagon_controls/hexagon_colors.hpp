#include <ArduinoBLE.h>
#include <FastLED.h>

#include "hexagon_constants.hpp"

CRGB hexagonLeds[HEXAGON_LEDS_COUNT];
BLEService hexagonsColorService("hexagons-colors-service");
BLEIntCharacteristic hexagonsColorCharacteristic("hexagons-color", BLERead | BLEWrite);

void setupHexagonsColorBLE();
void onHexagonsColorChange(BLEDevice central, BLECharacteristic characteristic);
void setHexagonsColor(CRGB color);

void setupHexagonsColorBLE()
{
    BLE.setAdvertisedService(hexagonsColorService);
    hexagonsColorCharacteristic.setEventHandler(BLEWritten, onHexagonsColorChange);
    hexagonsColorService.addCharacteristic(hexagonsColorCharacteristic);
    BLE.addService(hexagonsColorService);
}

void onHexagonsColorChange(BLEDevice central, BLECharacteristic characteristic)
{
    uint32_t newColor;
    characteristic.readValue(newColor);
    setHexagonsColor(CRGB(newColor));
}

void setHexagonsColor(CRGB color)
{
    for (int i = 0; i < HEXAGON_LEDS_COUNT; i++)
    {
        hexagonLeds[i] = color;
    }
    FastLED.show();
}
