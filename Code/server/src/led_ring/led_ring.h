#ifndef LED_RING_H
#define LED_RING_H

#include <stdint.h>

int led_ring_init(void);

void led_ring_turn_off(void);

void led_ring_set_color(uint8_t r, uint8_t g, uint8_t b);

#endif
