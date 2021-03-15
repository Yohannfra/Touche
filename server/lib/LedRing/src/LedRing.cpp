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

void LedRing::set_color(color_t color, uint8_t start, uint8_t end)
{
    for (size_t i = start; i < end; i++) {
        this->strip.setPixelColor(i, color.r, color.g, color.b);
    }
    this->strip.show();
}

void LedRing::do_circle_annimation(color_t color, uint8_t step)
{
    uint8_t index = step % NB_NEOPIXEL;

    if (this->strip.getPixelColor(index) != 0) {
        this->strip.setPixelColor(index, 0, 0, 0);
    } else {
        this->strip.setPixelColor(index, color.r, color.g, color.b);
    }
    this->strip.show();
    delay(100);

    // for (size_t i = 0; i < NB_NEOPIXEL; i++) {
    //     this->strip.setPixelColor(i, color.r, color.g, color.b);
    //     this->strip.getPixelColor()
    //     this->strip.show();
    //     delay(100);
    // }
    // for (size_t i = 0; i < NB_NEOPIXEL; i++) {
    //     this->strip.setPixelColor(i, 0, 0, 0);
    //     this->strip.show();
    //     delay(100);
    // }
    // this->turn_off();
}

void LedRing::blink(color_t color, int time_ms, size_t nb_blinks, uint8_t index)
{
    for (size_t i = 0; i < nb_blinks; i++) {
#if NB_NEOPIXEL_RING == 1
        (void)index;
        set_color(color, 0, NEOPIXEL_RING_SIZE);
#else
        set_color(color, index, NEOPIXEL_RING_SIZE * 2);
#endif
        delay(time_ms);
        turn_off();
        delay(time_ms);
    }
}

void LedRing::set_half_colors(color_t color_1, color_t color_2)
{
    for (size_t i = 0; i < NB_NEOPIXEL; i++) {
        if (i % 2)
            this->strip.setPixelColor(i, color_1.r, color_1.g, color_1.b);
        else
            this->strip.setPixelColor(i, color_2.r, color_2.g, color_2.b);
    }
    this->strip.show();
}

void LedRing::show_hits(hit_type_e hit_type)
{
#if NB_NEOPIXEL_RING == 1
    if (hit_type == HIT_PLAYER_1) {
        this->set_color(RED_RGB);
    } else if (hit_type == HIT_PLAYER_2) {
        this->set_color(GREEN_RGB);
    } else {
        this->set_half_colors(RED_RGB, GREEN_RGB);
    }
#else
    if (hit_type == HIT_PLAYER_1) {
        this->set_color(RED_RGB);
    } else if (hit_type == HIT_PLAYER_2) {
        this->set_color(GREEN_RGB, NEOPIXEL_RING_SIZE, NEOPIXEL_RING_SIZE * 2);
    } else {
        this->set_color(RED_RGB);
        this->set_color(GREEN_RGB, NEOPIXEL_RING_SIZE, NEOPIXEL_RING_SIZE * 2);
    }
#endif
}