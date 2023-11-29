#ifndef COLOR_H
#define COLOR_H

#include "FastLED.h"

void setupColor();
void handleColorCommand(String command);
void setHexagonsColor(CRGB color);
CRGB getCurrentColor();

#endif