#pragma once

#include <Arduino.h>

#define BYTESPERDRIVER 36
#define LEDDOTSPERDRIVER 24


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
    TLC5947(uint16_t* ledData, uint16_t nLedDots, uint8_t dataPin, uint8_t clkPin, uint8_t latchPin, int8_t enablePin=-1, uint32_t clkFrequency=10000000);
    void update();
};