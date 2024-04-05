#include <Arduino.h>
#include <SPI.h>

#include "TLC5947.h"

// pinout:
#define LATCH_PIN 22
#define OE_PIN 21
#define DATA_PIN 23
#define CLK_PIN 18

// hardware setup:
#define N_LEDDOTS 25

// SPI Config:
#define SPI_FREQ 1000000 // 10MHz

// led data:
uint16_t leds[N_LEDDOTS];

// create the TLC5947 object:
// The led array needs to be initialized prior to this object creation
TLC5947 ledDriver(leds, N_LEDDOTS, DATA_PIN, CLK_PIN, LATCH_PIN);

uint32_t loopCounter = 0;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    uint32_t start = micros();
    setAllLedsTo(0xFF);
    uint32_t updateStart = micros();
    ledDriver.update();
    uint32_t clearStart = micros();
    clearLeds();
    uint32_t secondUpdateStart = micros();
    ledDriver.update();
    uint32_t secondUpdateDone = micros();

    if (loopCounter % 1000 == 0) {
        Serial.println("All Leds to full: " + String(updateStart - start) + "us\nFirst update: " + String(clearStart - updateStart) + "us\nAll leds off: " + String(secondUpdateStart - clearStart) + "us\nsecondUpdate: " + String(secondUpdateDone - secondUpdateStart) + "us\n\n");
    }
    loopCounter++;
}

void clearLeds()
{
    for (int i = 0; i < N_LEDDOTS; i++) {
        leds[i] = 0;
    }
}

void setAllLedsTo(uint16_t brightness)
{
    for (int i = 0; i < N_LEDDOTS; i++) {
        leds[i] = brightness;
    }
}