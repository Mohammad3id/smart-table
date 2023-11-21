#include <ArduinoBLE.h>
#include <FastLED.h>

#include "../../constants/constants.hpp"

CRGB ledsColor[HEXAGON_LEDS_COUNT];
BLEService colorService("color-service");
BLEIntCharacteristic colorCharacteristic("color", BLERead | BLEWrite);


void onColorChange(BLEDevice central, BLECharacteristic characteristic);



void setupColor()
{
    FastLED.addLeds<NEOPIXEL, HEXAGONS_COLOR_PIN>(ledsColor, HEXAGON_LEDS_COUNT);
}

void setupColorBLE()
{
    BLE.setAdvertisedService(colorService);
    colorCharacteristic.setEventHandler(BLEWritten, onColorChange);
    colorService.addCharacteristic(colorCharacteristic);
    BLE.addService(colorService);
}

void onColorChange(BLEDevice central, BLECharacteristic characteristic)
{
    uint32_t newColor;
    characteristic.readValue(newColor);
    setHexagonsColor(CRGB(newColor));
}

void setHexagonsColor(CRGB color)
{
    for (int i = 0; i < HEXAGON_LEDS_COUNT; i++)
    {
        ledsColor[i] = color;
    }
    FastLED.show();
}
