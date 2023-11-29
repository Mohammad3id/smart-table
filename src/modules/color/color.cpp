#include <FastLED.h>

#include "color.hpp"
#include "../../constants/constants.hpp"

CRGB ledsColor[HEXAGON_LEDS_COUNT];

void setupColor()
{
    FastLED.addLeds<NEOPIXEL, HEXAGONS_COLOR_PIN>(ledsColor, HEXAGON_LEDS_COUNT);
}


void handleColorCommand(String command)
{
    String newColorCode = command.substring(4);
    setHexagonsColor(CRGB(std::stoi(newColorCode.c_str(), 0, 16)));
}

void setHexagonsColor(CRGB color)
{
    for (int i = 0; i < HEXAGON_LEDS_COUNT; i++)
    {
        ledsColor[i] = color;
    }
    FastLED.show();
}

CRGB getCurrentColor()
{
    return ledsColor[0];
}
