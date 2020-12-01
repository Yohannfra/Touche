#ifndef LEDRING_HPP
#define LEDRING_HPP

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define RED_RGB 0xFF, 0, 0
#define GREEN_RGB 0, 0xFF, 0

static const uint8_t COLOR_CODE[2][3] = {{RED_RGB}, {GREEN_RGB}};

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
    void set_half_colors(byte r, byte g, byte b,
                    byte r2, byte g2, byte b2);
    void blink(byte r, byte g, byte b, int time_ms, size_t nb_blinks = 3);
    void blink(const uint8_t rgb[3], int time_ms, size_t nb_blinks = 3);

};




#endif /* LEDRING_HPP */