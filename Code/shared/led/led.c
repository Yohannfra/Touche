#include "led.h"

#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <stdlib.h>

#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#    define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)
#    define PIN DT_GPIO_PIN(LED0_NODE, gpios)
#    define FLAGS DT_GPIO_FLAGS(LED0_NODE, gpios)
#endif

static const struct device *led_dev;

int led_init()
{
    int ret;

    led_dev = device_get_binding(LED0);
    if (led_dev == NULL) {
        return EXIT_FAILURE;
    }

    ret = gpio_pin_configure(led_dev, PIN, GPIO_OUTPUT_INACTIVE | FLAGS);
    if (ret < 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void led_set()
{
    gpio_pin_set(led_dev, PIN, 1);
}

void led_clear()
{
    gpio_pin_set(led_dev, PIN, 0);
}

void led_toggle()
{
    gpio_pin_toggle(led_dev, PIN);
}

void led_blink(int delay_ms, uint8_t nb_times)
{
    led_clear();
    for (uint8_t i = 0; i < nb_times; i++) {
        led_toggle();
        k_sleep(K_MSEC(1000));
    }
    led_clear();
}
