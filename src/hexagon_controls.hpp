#include <ArduinoBLE.h>
#include <FastLED.h>


#define HEXAGONS_COUNT 21
#define HEXAGON_LEDS_COUNT 21
#define HEXAGONS_COLOR_PIN 15

#define LATCH_PIN 12
#define CLOCK_PIN 13
#define DATA_PIN_1 14
#define DATA_PIN_2 16
#define DATA_PIN_3 17


const char* hexagonUUIDs[HEXAGONS_COUNT] = {
    "hexagon-0",
    "hexagon-1",
    "hexagon-2",
    "hexagon-3",
    "hexagon-4",
    "hexagon-5",
    "hexagon-6",
    "hexagon-7",
    "hexagon-8",
    "hexagon-9",
    "hexagon-10",
    "hexagon-11",
    "hexagon-12",
    "hexagon-13",
    "hexagon-14",
    "hexagon-15",
    "hexagon-16",
    "hexagon-17",
    "hexagon-18",
    "hexagon-19",
    "hexagon-20",
};

CRGB hexagonLeds[HEXAGON_LEDS_COUNT];

BLEService hexagonsColorService("hexagons-colors-service");
BLEIntCharacteristic hexagonsColorCharacteristic("hexagons-color", BLERead | BLEWrite);

BLEService hexagonsPowerService("hexagons-power-service");
BLEBoolCharacteristic* hexagonsPowerCharacteristic[HEXAGONS_COUNT];
byte hexagonPowers[3];

void setupHexagons();
void setupHexagonsBLE();
void setupHexagonsColorBLE();
void setupHexagonsPowerBLE();
void onHexagonsColorChange(BLEDevice central, BLECharacteristic characteristic);
void onHexagonsPowerChange(BLEDevice central, BLECharacteristic characteristic);
void setHexagonsColor(CRGB color);
void turnOnHexagon(int hexagonIndex);
void turnOffHexagon(int hexagonIndex);
void switchHexagon(int hexagonIndex, bool power);

void setupHexagons()
{
    FastLED.addLeds<NEOPIXEL, HEXAGONS_COLOR_PIN>(hexagonLeds, HEXAGON_LEDS_COUNT);
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN_1, OUTPUT);
    pinMode(DATA_PIN_2, OUTPUT);
    pinMode(DATA_PIN_3, OUTPUT);
}

void setupHexagonsBLE()
{
    setupHexagonsColorBLE();
    setupHexagonsPowerBLE();
    BLE.setLocalName("Smart Table");
    BLE.advertise();
}

void setupHexagonsColorBLE()
{
    BLE.setAdvertisedService(hexagonsColorService);
    hexagonsColorCharacteristic.setEventHandler(BLEWritten, onHexagonsColorChange);
    hexagonsColorService.addCharacteristic(hexagonsColorCharacteristic);
    BLE.addService(hexagonsColorService);
}

void setupHexagonsPowerBLE()
{
    BLE.setAdvertisedService(hexagonsPowerService);
    for (int i = 0; i < HEXAGONS_COUNT; i++)
    {
        auto characteristic = BLEBoolCharacteristic(hexagonUUIDs[i], BLERead | BLEWrite);
        characteristic.setEventHandler(BLEWritten, onHexagonsPowerChange);
        hexagonsPowerService.addCharacteristic(characteristic);
        hexagonsPowerCharacteristic[i] = &characteristic;
    }
    BLE.addService(hexagonsPowerService);
}

void onHexagonsColorChange(BLEDevice central, BLECharacteristic characteristic)
{
    uint32_t newColor;
    characteristic.readValue(newColor);
    setHexagonsColor(CRGB(newColor));
}

void onHexagonsPowerChange(BLEDevice central, BLECharacteristic characteristic)
{
    auto index = atoi(&characteristic.uuid()[8]);
    byte power;
    characteristic.readValue(power);
    if (power)
    {
        turnOnHexagon(index);
    }
    else
    {
        turnOffHexagon(index);
    }
}

void setHexagonsColor(CRGB color)
{
    for (int i = 0; i < HEXAGON_LEDS_COUNT; i++)
    {
        hexagonLeds[i] = color;
    }
    FastLED.show();
}

void turnOnHexagon(int hexagonIndex)
{
    switchHexagon(hexagonIndex, HIGH);

    Serial.print("Hexagon ");
    Serial.print(hexagonIndex);
    Serial.println(": ON");
}

void turnOffHexagon(int hexagonIndex)
{
    switchHexagon(hexagonIndex, LOW);
    Serial.print("Hexagon ");
    Serial.print(hexagonIndex);
    Serial.println(": OFF");
}

void switchHexagon(int hexagonIndex, bool power)
{
    digitalWrite(LATCH_PIN, LOW);
    byte bitsToSend = hexagonPowers[hexagonIndex / 8];
    if (power)
    {
        bitsToSend = bitsToSend || 1 << hexagonIndex;
    }
    else
    {
        bitsToSend = bitsToSend && ~(1 << hexagonIndex);
    }

    uint8_t dataPin;
    switch (hexagonIndex / 8)
    {
    case 0:
        dataPin = DATA_PIN_1;
        break;
    case 1:
        dataPin = DATA_PIN_2;
        break;
    case 2:
        dataPin = DATA_PIN_3;
        break;
    default:
        break;
    }

    shiftOut(dataPin, CLOCK_PIN, MSBFIRST, bitsToSend);
    hexagonPowers[hexagonIndex / 8] = bitsToSend;

    digitalWrite(LATCH_PIN, HIGH);
}