// #include <Arduino.h>
// #include <ArduinoBLE.h>
#include <FastLED.h>
// #include <ReactESP.h>

#include "BluetoothSerial.h"
#include "BluetoothA2DP.h"


// #include "setup/setup.hpp"
// #include "async/async.hpp"

// reactesp::ReactESP app(true);
BluetoothA2DPSink a2dp_sink;
BluetoothSerial SerialBT;

void setup()
{
  Serial.begin(115200);

  // if (!BLE.begin()) {
  //   Serial.println("- Starting Bluetooth® Low Energy module failed!");
  //   while (1);
  // }
  // setupTable();
  // setupTableBLE();

  a2dp_sink.start("Smart Table");

}

void loop()
{
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  
  // async.tick();
}