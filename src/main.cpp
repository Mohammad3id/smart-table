#include <Arduino.h>
#include <ArduinoBLE.h>
#include <FastLED.h>

#include "hexagon_controls/hexagon_setup.hpp"

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

}