#include <ReactESP.h>

#include "modes.hpp"
#include "../../async/async.hpp"
#include "../color/color.hpp"
#include "../../utils/utils.hpp"
#include "../../constants/constants.hpp"


reactesp::Reaction* currentLoop;
String currentMode = MODE_NORMAL;

void enableColorfulMode();
void enableNormalMode();

void setupModes()
{
    // In case of any future setups
}

void handleModeCommand(String command)
{
    auto newMode = command.substring(4);
    if (newMode.equals(MODE_COLORFUL)) {
        enableColorfulMode();
    } else {
        Serial.println("Enabling Normal Mode");
        enableNormalMode();
    }
}

void enableNormalMode()
{
    if (currentMode.equals(MODE_NORMAL)) return;

    if (currentLoop)
    {
        currentLoop->remove();
        currentLoop = NULL;
    }
    setHexagonsColor(getCurrentColor());
    currentMode = MODE_NORMAL;
}

void enableColorfulMode()
{
    if (currentMode.equals(MODE_COLORFUL)) return;

    Serial.println("Enabling Colorful Mode");

    if (currentLoop)
    {
        Serial.println("Stopping other modes");
        currentLoop->remove();
        currentLoop = NULL;
    }

    
    Serial.println("Initializing loop variables");

    static CRGB startColor;
    static CRGB endColor;
    static int i;
    static const int steps = 20;

    
    i = 0;
    startColor = getCurrentColor();
    endColor = getRandomColor();
    
    Serial.println("Starting loop");

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

    Serial.println("Loop started");

    currentMode = MODE_COLORFUL;
}
