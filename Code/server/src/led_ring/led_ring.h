#ifndef LED_RING_H
#define LED_RING_H

#include <stdint.h>

#define RGB_COLOR_GREEN 0x00, 0xff, 0x00
#define RGB_COLOR_RED 0xff, 0x00, 0x00

int led_ring_init(void);

void led_ring_turn_off(void);

void led_ring_set_color(uint8_t r, uint8_t g, uint8_t b);

void led_ring_play_demo(void);

#endif
