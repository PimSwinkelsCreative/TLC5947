#include "TLC5947.h"
#include <SPI.h>

TLC5947::TLC5947(uint16_t* leds, uint16_t nLedDots, uint8_t dataPin, uint8_t clkPin, uint8_t latchPin, int8_t enablePin, uint32_t clkFrequency)
{
    this->leds = leds;
    this->nLedDots = nLedDots;
    this->dataPin = dataPin;
    this->clkPin = clkPin;
    this->latchPin = latchPin;
    this->enablePin = enablePin;
    this->clkFrequency = clkFrequency;

    nLedDrivers = nLedDots / LEDDOTSPERDRIVER;
    if (nLedDots % LEDDOTSPERDRIVER > 0) {
        nLedDrivers++;
    }
    init();
}

TLC5947::TLC5947(RGBLed* rgbLedData, uint16_t nRGBLeds, uint8_t dataPin, uint8_t clkPin, uint8_t latchPin, int8_t enablePin, uint32_t clkFrequency)
{
    TLC5947 tempDriver((uint16_t*)rgbLedData, nRGBLeds * sizeof(rgbLedData[0]) / sizeof(rgbLedData[0].r), dataPin, clkPin, latchPin, enablePin, clkFrequency);
    *this = tempDriver;
}

TLC5947::TLC5947(RGBWLed* rgbwLedData, uint16_t nRGBWLeds, uint8_t dataPin, uint8_t clkPin, uint8_t latchPin, int8_t enablePin, uint32_t clkFrequency)
{
    TLC5947 tempdriver((uint16_t*)rgbwLedData, nRGBWLeds * sizeof(rgbwLedData[0]) / sizeof(rgbwLedData[0].r), dataPin, clkPin, latchPin, enablePin, clkFrequency);
    *this = tempdriver;
}

void TLC5947::init()
{
    pinMode(latchPin, OUTPUT);
    if (enablePin > 0)
        pinMode(enablePin, OUTPUT);
    SPI.begin(clkPin, -1, dataPin, -1);
    SPI.setFrequency(clkFrequency);
    digitalWrite(latchPin, HIGH);
}

void TLC5947::update()
{
    uint32_t startTime = micros();
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
                ledData[BYTESPERDRIVER - i * 12 / 8 - 1] += (leds[i + ledStartIndex] & 0xF) << 4; // add the 4 LSB to the bytes MSB
                ledData[BYTESPERDRIVER - i * 12 / 8 - 2] = (leds[i + ledStartIndex] & 0xFF0) >> 4; // fill with the 8 MSB
            }
        }
        SPI.writeBytes(ledData, BYTESPERDRIVER);
    }
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    uint32_t updateTime = micros() - startTime;

    // Serial.println("update Took: "+String(updateTime)+"us");
}