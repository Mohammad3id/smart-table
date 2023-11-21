#include <FastLED.h>

CRGB interpolateColor(CRGB startColor, CRGB endColor, int step, int steps)
{
  short r = (int)startColor.r + ((int)endColor.r - (int)startColor.r) * step / steps;
  short g = (int)startColor.g + ((int)endColor.g - (int)startColor.g) * step / steps;
  short b = (int)startColor.b + ((int)endColor.b - (int)startColor.b) * step / steps;

  return CRGB(r, g, b);
}