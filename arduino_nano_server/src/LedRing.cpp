#include "LedRing.hpp"

LedRing::LedRing(byte pin)
{
    this->pin = pin;
    this->strip = Adafruit_NeoPixel(NB_NEOPIXEL, this->pin, NEO_GRB + NEO_KHZ800);

    this->strip.begin();
    this->strip.setBrightness(50);
    this->strip.show();
}

void LedRing::turn_off()
{
    this->strip.clear();
    // this->strip.show(); // Not sure
}

void LedRing::set_color(byte r, byte g, byte b)
{
    for (size_t i = 0; i < NB_NEOPIXEL; i++) {
        this->strip.setPixelColor(i, r, g, b);
    }
    this->strip.show();
}