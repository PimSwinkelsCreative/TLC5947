#pragma once
#include <Arduino.h>
#define BYTESPERDRIVER 36
#define LEDDOTSPERDRIVER 24

// create an RGBWLed struct:
struct RGBWLed {
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t w;
};

// create a RGBLed struct:
struct RGBLed {
    uint16_t r;
    uint16_t g;
    uint16_t b;
};

class TLC5947 {
private:
    uint16_t* leds;
    uint16_t nLedDots;
    uint8_t dataPin;
    uint8_t clkPin;
    uint8_t latchPin;
    int8_t enablePin;
    uint32_t clkFrequency;
    uint8_t nLedDrivers;

    void init();

public:
    TLC5947(RGBLed* rgbLedData, uint16_t nRRGBLeds, uint8_t dataPin, uint8_t clkPin, uint8_t latchPin, int8_t enablePin = -1, uint32_t clkFrequency = 10000000);
    TLC5947(RGBWLed* rgbwLedData, uint16_t nRRGBWLeds, uint8_t dataPin, uint8_t clkPin, uint8_t latchPin, int8_t enablePin = -1, uint32_t clkFrequency = 10000000);
    TLC5947(uint16_t* ledData, uint16_t nLedDots, uint8_t dataPin, uint8_t clkPin, uint8_t latchPin, int8_t enablePin = -1, uint32_t clkFrequency = 10000000);
    void update();
};