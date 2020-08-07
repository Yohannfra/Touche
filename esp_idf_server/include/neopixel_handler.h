#ifndef NEOPIXEL_HANDLER_H
#define NEOPIXEL_HANDLER_H

#include <stdint.h>
#include <stdbool.h>
#include "neopixel.h"

#define NB_LED 12


// WTF RED ET GREEN SONT SWAP

#define GREEN 0xFF, 0, 0

#define RED 0, 0xFF, 0

#define ORANGE 0x7F, 0xFF, 0

typedef struct neopixel_data_s
{
    uint32_t pixels_array[NB_LED];
    pixel_settings_t px;
    int gpio;
    rmt_channel_t channel;
    bool is_on;
}   neopixel_data_t;

void init_neopixel(neopixel_data_t *neopixel_data);
void turn_off_neopixel(neopixel_data_t *neopixel_data);
void set_color_neopixel(neopixel_data_t *neopixel_data, int r, int g, int b);

#endif /* NEOPIXEL_HANDLER_H */