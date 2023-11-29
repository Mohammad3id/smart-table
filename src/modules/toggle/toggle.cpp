#include <FastLED.h>

#include "toggle.hpp"
#include "../../constants/constants.hpp"
#include "../../utils/utils.hpp"

uint32_t hexagonPowers;

void setupToggle()
{
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
}

void handleToggleCommand(String command)
{
    auto strIndex = command.substring(4);
    strIndex.replace("-on", "");
    strIndex.replace("-off", "");
    int index = strIndex.toInt();
    
    auto power = command.endsWith("on");

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
}