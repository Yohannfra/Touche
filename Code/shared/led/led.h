#ifndef LED_H
#define LED_H

#include <stdint.h>

int led_init();

void led_set();

void led_clear();

void led_toggle();

void led_blink(int delay_ms, uint8_t nb_times);

#endif
