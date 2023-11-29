#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <FastLED.h>

String binaryString(uint32_t num, int digitsCount);
CRGB interpolateColor(CRGB startColor, CRGB endColor, int step, int steps);
CRGB getRandomColor();

#endif