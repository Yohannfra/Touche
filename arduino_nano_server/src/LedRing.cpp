#include "LedRing.hpp"

LedRing::LedRing(byte pin) : strip(NB_NEOPIXEL, pin, NEO_GRB + NEO_KHZ800)
{
    this->pin = pin;
}

void LedRing::init()
{
    this->strip.begin();
    this->strip.setBrightness(50);
    this->strip.show();
}

void LedRing::turn_off()
{
    this->strip.clear();
    this->strip.show();
}

void LedRing::set_color(byte r, byte g, byte b)
{
    for (size_t i = 0; i < NB_NEOPIXEL; i++) {
        this->strip.setPixelColor(i, r, g, b);
    }
    this->strip.show();
}