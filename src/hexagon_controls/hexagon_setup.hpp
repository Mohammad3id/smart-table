#include <ArduinoBLE.h>
#include <FastLED.h>

#include "hexagon_constants.hpp"
#include "hexagon_colors.hpp"
#include "hexagon_power.hpp"

void setupHexagons();
void setupHexagonsBLE();

void setupHexagons()
{
    FastLED.addLeds<NEOPIXEL, HEXAGONS_COLOR_PIN>(hexagonLeds, HEXAGON_LEDS_COUNT);
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
}

void setupHexagonsBLE()
{
    setupHexagonsColorBLE();
    setupHexagonsPowerBLE();
    BLE.setLocalName("Smart Table");
    BLE.advertise();
}

