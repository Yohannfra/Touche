#include "neopixel.h"

#include <unistd.h>
#include "freertos/task.h"
#include <string.h>
#include "esp_log.h"
#include "server.h"
#include "neopixel_handler.h"

#define NEOPIXEL_WS2812 // The type of neopixel i use

void init_neopixel(neopixel_data_t *np_data)
{
    neopixel_init(np_data->gpio, np_data->channel);

    for (int i = 0; i < NB_LED; i++) {
        np_data->pixels_array[i] = 0;
    }
    np_data->px.pixels = (uint8_t *)np_data->pixels_array;
    np_data->px.pixel_count = NB_LED;
    strcpy(np_data->px.color_order, "RGB");

    memset(&np_data->px.timings, 0, sizeof(np_data->px.timings));
    np_data->px.timings.mark.level0 = 1;
    np_data->px.timings.space.level0 = 1;
    np_data->px.timings.mark.duration0 = 12;
    np_data->px.nbits = 24;
    np_data->px.timings.mark.duration1 = 14;
    np_data->px.timings.space.duration0 = 7;
    np_data->px.timings.space.duration1 = 16;
    np_data->px.timings.reset.duration0 = 600;
    np_data->px.timings.reset.duration1 = 600;
    np_data->px.brightness = 0x80;

    np_data->is_on = false;
}

void turn_off_neopixel(neopixel_data_t *np_data)
{
    np_clear(&np_data->px);
    np_show(&np_data->px, np_data->channel);
    np_data->is_on = false;
    usleep(1000 * 10);
}

uint32_t color_rgb_to_int(int r, int g, int b)
{
    return ((r << 24) + (g << 16) + (b << 8));
}

void set_color_neopixel(neopixel_data_t *np_data, int r, int g, int b)
{
    uint32_t color = color_rgb_to_int(r, g, b);

    for (int i = 0; i < NB_LED; i++) {
        np_set_pixel_color(&np_data->px, i, color);
    }
    np_data->is_on = true;
    np_show(&np_data->px, np_data->channel);
    usleep(1000 * 10);
}

void test_neopixels_blink(neopixel_data_t *np1, neopixel_data_t *np2)
{
    while (1) {
        set_color_neopixel(np1, GREEN);
        set_color_neopixel(np2, RED);

        vTaskDelay(1000 / portTICK_PERIOD_MS);

        turn_off_neopixel(np1);
        turn_off_neopixel(np2);

        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }
}