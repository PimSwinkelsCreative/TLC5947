#pragma once
#include <Arduino.h>
#define BYTESPERDRIVER 36
#define LEDDOTSPERDRIVER 24

#define DEFAULT_SPI_CLK 10000000  // 10MHz

// create a pinout struct:
struct TLC5947_PINOUT {
  uint8_t clkPin;
  uint8_t dataPin;
  uint8_t latchPin;
  uint8_t blankPin;
};

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
  TLC5947_PINOUT pinout;
  uint32_t clkFrequency;
  uint8_t nLedDrivers;

  void init();

 public:
  TLC5947(RGBLed* _rgbLedData, uint16_t _nRGBLeds, TLC5947_PINOUT& _pinout,
          uint32_t _clkFrequency = DEFAULT_SPI_CLK);
  TLC5947(RGBWLed* _rgbwLedData, uint16_t _nRGBWLeds, TLC5947_PINOUT& _pinout,
          uint32_t _clkFrequency = DEFAULT_SPI_CLK);
  TLC5947(uint16_t* _ledData, uint16_t _nLedDots, TLC5947_PINOUT& _pinout,
          uint32_t _clkFrequency = DEFAULT_SPI_CLK);
  void update();
};