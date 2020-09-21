#ifndef LEDRING_HPP
#define LEDRING_HPP

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define RED_RGB 0xFF, 0, 0
#define GREEN_RGB 0, 0xFF, 0

#define NB_NEOPIXEL 12

class LedRing
{
private:
    byte pin;
    Adafruit_NeoPixel strip;

public:
    LedRing(byte pin);
    void turn_off();
    void init();
    void set_color(byte r, byte g, byte b);
};




#endif /* LEDRING_HPP */