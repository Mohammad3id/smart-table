#include <Arduino.h>
#include <ArduinoBLE.h>
#include <FastLED.h>

#include "hexagon_controls.hpp"


void setup()
{
  Serial.begin(115200);

  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }
  setupHexagonsBLE();
  setupHexagons();
}

void loop()
{

  BLEDevice central = BLE.central();
  if (central)
  {
    Serial.println("Connected");
    while (central.connected())
    {
      // FastLED.show();
    }
    Serial.println("Disconnected");
  }

  // setHexagonsColor(CRGB::White);
  // delay(1000);
  // setHexagonsColor(CRGB::Aqua);
  // delay(1000);
}



// CRGB interpolateColor(CRGB startColor, CRGB endColor, int step, int steps)
// {
//   short r = (int)startColor.r + ((int)endColor.r - (int)startColor.r) * step / steps;
//   short g = (int)startColor.g + ((int)endColor.g - (int)startColor.g) * step / steps;
//   short b = (int)startColor.b + ((int)endColor.b - (int)startColor.b) * step / steps;

//   return CRGB(r, g, b);
// }
