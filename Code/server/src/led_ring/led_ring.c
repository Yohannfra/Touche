#include "led_ring.h"

#include <device.h>
#include <devicetree.h>
#include <drivers/led_strip.h>
#include <drivers/spi.h>
#include <logging/log.h>
#include <stdlib.h>
#include <sys/util.h>
#include <zephyr.h>

LOG_MODULE_REGISTER(led_ring, LOG_LEVEL_INF);

#define STRIP_NODE DT_ALIAS(led_strip)
#define STRIP_NUM_PIXELS DT_PROP(DT_ALIAS(led_strip), chain_length)

static struct led_rgb pixels[STRIP_NUM_PIXELS];

static const struct device *strip = DEVICE_DT_GET(STRIP_NODE);

int led_ring_init(void)
{
    if (device_is_ready(strip)) {
        LOG_INF("Found LED strip device %s", strip->name);
    } else {
        LOG_ERR("LED strip device %s is not ready", strip->name);
        return EXIT_FAILURE;
    }
    led_ring_turn_off();
    return EXIT_SUCCESS;
}

void led_ring_turn_off(void)
{
    memset(pixels, 0x00, sizeof(pixels));
    int rc = led_strip_update_rgb(strip, pixels, STRIP_NUM_PIXELS);

    if (rc) {
        LOG_ERR("couldn't update strip: %d", rc);
    }
}

void led_ring_set_color(uint8_t r, uint8_t g, uint8_t b)
{
    struct led_rgb color ={0, r, g, b};

    for (int i = 0; i < STRIP_NUM_PIXELS; i++) {
        memcpy(&pixels[i], &color, sizeof(struct led_rgb));
    }

    int rc = led_strip_update_rgb(strip, pixels, STRIP_NUM_PIXELS);

    if (rc) {
        LOG_ERR("couldn't update strip: %d", rc);
    }
}

void led_ring_play_demo(void)
{
    while (1) {
        LOG_INF("GREEN");
        led_ring_set_color(0xff, 0, 0);
        k_sleep(K_MSEC(500));

        LOG_INF("RED");
        led_ring_set_color(0, 0xff, 0);
        k_sleep(K_MSEC(500));

        LOG_INF("BLUE");
        led_ring_set_color(0, 0, 0xff);
        k_sleep(K_MSEC(500));
    }
}
