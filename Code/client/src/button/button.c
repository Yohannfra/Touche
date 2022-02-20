#include "button.h"

#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <stdlib.h>

#define SW0_NODE DT_ALIAS(sw0)

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET_OR(SW0_NODE, gpios, {0});

int button_init()
{
    int ret;

    if (!device_is_ready(button.port)) {
        printk("Error: button device %s is not ready\n", button.port->name);
        return EXIT_FAILURE;
    }

    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret != 0) {
        printk("Error %d: failed to configure %s pin %d\n", ret, button.port->name, button.pin);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

bool button_get_state()
{
    return gpio_pin_get_dt(&button);
}
