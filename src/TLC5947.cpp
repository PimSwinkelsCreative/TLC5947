#include "TLC5947.h"

#include <SPI.h>

TLC5947::TLC5947(uint16_t* _ledData, uint16_t _nLedDots, uint8_t _clkPin, uint8_t _dataPin, uint8_t _latchPin, int8_t _blankPin, uint32_t _clkFrequency)
    : leds(_ledData)
    , nLedDots(_nLedDots)
    , clkPin(_clkPin)
    , dataPin(_dataPin)
    , latchPin(_latchPin)
    , blankPin(_blankPin)
    , clkFrequency(_clkFrequency)
{
    init();
}

TLC5947::TLC5947(RGBColor* _rgbLedData, uint16_t _nRGBLeds, uint8_t _clkPin, uint8_t _dataPin, uint8_t _latchPin, int8_t _blankPin, uint32_t _clkFrequency)
    : leds((uint16_t*)_rgbLedData)
    , nLedDots(_nRGBLeds * (sizeof(_rgbLedData[0]) / sizeof(_rgbLedData[0].r)))
    , clkPin(_clkPin)
    , dataPin(_dataPin)
    , latchPin(_latchPin)
    , blankPin(_blankPin)
    , clkFrequency(_clkFrequency)
{
    init();
}

TLC5947::TLC5947(RGBWColor* _rgbwData, uint16_t _nRGBWLeds, uint8_t _clkPin, uint8_t _dataPin, uint8_t _latchPin, int8_t _blankPin, uint32_t _clkFrequency)
    : leds((uint16_t*)_rgbwData)
    , nLedDots(_nRGBWLeds * (sizeof(_rgbwData[0]) / sizeof(_rgbwData[0].r)))
    , clkPin(_clkPin)
    , dataPin(_dataPin)
    , latchPin(_latchPin)
    , blankPin(_blankPin)
    , clkFrequency(_clkFrequency)
{
    init();
}

void TLC5947::init()
{
    nLedDrivers = nLedDots / LEDDOTSPERDRIVER;
    if (nLedDots % LEDDOTSPERDRIVER > 0) {
        nLedDrivers++;
    }
    pinMode(latchPin, OUTPUT);
    SPI.begin(clkPin, -1, dataPin, -1);
    SPI.setFrequency(clkFrequency);
    digitalWrite(latchPin, HIGH);
    if (blankPin > 0) {
        pinMode(blankPin, OUTPUT);
        digitalWrite(blankPin, LOW);
    }
}

void TLC5947::update()
{
    for (int driverNr = nLedDrivers - 1; driverNr >= 0; driverNr--) {
        // create an array for the next chunk to send over SPI:
        uint8_t ledData[BYTESPERDRIVER];
        memset(ledData, 0, sizeof(ledData));

        uint16_t ledStartIndex = driverNr * BYTESPERDRIVER * 8 / 12;
        for (int i = 0; i < LEDDOTSPERDRIVER; i++) {
            if (i + ledStartIndex >= nLedDots)
                break;

            // copy the led values to the correct bits in the ledData Array
            if (i % 2 == 0) {
                ledData[BYTESPERDRIVER - i * 12 / 8 - 1] = leds[i + ledStartIndex] & 0xFF; // fill with the 8 LSB
                ledData[BYTESPERDRIVER - i * 12 / 8 - 2] += (leds[i + ledStartIndex] & 0xF00) >> 8; // add the 4 MSB to the bytes LSB
            } else {
                ledData[BYTESPERDRIVER - i * 12 / 8 - 1] += (leds[i + ledStartIndex] & 0xF)
                    << 4; // add the 4 LSB to the bytes MSB
                ledData[BYTESPERDRIVER - i * 12 / 8 - 2] = (leds[i + ledStartIndex] & 0xFF0) >> 4; // fill with the 8 MSB
            }
        }
        SPI.writeBytes(ledData, BYTESPERDRIVER);
    }

    // outputs are briefly disabled when latching the values.
    // This should solve the flickering problem
    if (blankPin > 0)
        digitalWrite(blankPin, HIGH);
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
    if (blankPin > 0)
        digitalWrite(blankPin, LOW);
}

void TLC5947::setLedTo(uint16_t ledIndex, struct RGBWColor color)
{
    ledIndex = ledIndex * sizeof(color) / sizeof(color.r);
    if (ledIndex >= nLedDots)
        return;
    memcpy(&leds[ledIndex], &color, sizeof(color));
}

void TLC5947::setLedTo(uint16_t ledIndex, struct RGBColor color)
{
    if (ledIndex >= nLedDots * sizeof(color) / sizeof(color.r))
        return;
    memcpy(&leds[ledIndex], &color, sizeof(color));
}

void TLC5947::setLedTo(uint16_t ledIndex, uint16_t brightness)
{
    if (ledIndex >= nLedDots)
        return; // catch out of bounds index
    leds[ledIndex] = brightness;
}

void TLC5947::setAllLedsTo(struct RGBWColor color)
{
    for (int i = 0; i < nLedDots; i++) {
        switch (i % 4) {
        case 0:
            leds[i] = color.r;
            break;
        case 1:
            leds[i] = color.g;
            break;
        case 2:
            leds[i] = color.b;
            break;
        case 3:
            leds[i] = color.w;
            break;
        default:
            leds[i] = 0; // should not occur
            break;
        }
    }
}
void TLC5947::setAllLedsTo(struct RGBColor color)
{
    for (int i = 0; i < nLedDots; i++) {
        switch (i % 3) {
        case 0:
            leds[i] = color.r;
            break;
        case 1:
            leds[i] = color.g;
            break;
        case 2:
            leds[i] = color.b;
            break;
        default:
            leds[i] = 0; // should not occur
            break;
        }
    }
}
void TLC5947::setAllLedsTo(uint16_t brightness)
{
    for (int i = 0; i < nLedDots; i++) {
        leds[i] = brightness;
    }
}

void TLC5947::clearLeds()
{
    for (int i = 0; i < nLedDots; i++) {
        leds[i] = 0;
    }
}