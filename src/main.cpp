#include <Arduino.h>
#include "async/async.hpp"
#include "setup/setup.hpp"


void executeCommand(String command);

void setup() {
  Serial.begin(115200);
  setupTable();
  setupBluetooth();
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  async.tick();
}
