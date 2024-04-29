#include <Arduino.h>
#include <SPI.h>

#include "TLC5947.h"

// pinout:
#define LATCH_PIN 22
#define OE_PIN 21
#define DATA_PIN 23
#define CLK_PIN 18

// hardware setup:
#define N_LEDS 48

// SPI Config:
#define SPI_FREQ 1000000 // 10MHz

// led data:
RGBWLed leds[N_LEDS];

// create the TLC5947 object:
// The led array needs to be initialized prior to this object creation
TLC5947 ledDriver(leds, N_LEDS, DATA_PIN, CLK_PIN, LATCH_PIN);

// TLC5947 ledDriver((uint16_t*)leds, N_LEDS*sizeof(leds[0])/sizeof(leds[0].r), DATA_PIN, CLK_PIN, LATCH_PIN);


uint32_t loopCounter = 0;

void setAllLedsTo(struct RGBWLed color)
{
    for (int i = 0; i < N_LEDS; i++) {
        memcpy(&leds[i], &color, sizeof(leds[0]));
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(OE_PIN, OUTPUT);
    digitalWrite(OE_PIN, LOW);
}

void loop()
{
    setAllLedsTo({ 4095, 0, 0, 0 });
    ledDriver.update();
    delay(500);
    setAllLedsTo({ 0, 4095, 0, 0 });
    ledDriver.update();
    delay(500);
    setAllLedsTo({ 0, 0, 4095, 0 });
    ledDriver.update();
    delay(500);
    setAllLedsTo({ 0, 0, 0, 4095 });
    ledDriver.update();
    delay(500);
}
