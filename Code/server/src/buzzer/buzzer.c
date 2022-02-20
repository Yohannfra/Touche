#include "buzzer.h"

#include <drivers/pwm.h>
#include <drivers/gpio.h>
#include <logging/log.h>
#include <stdlib.h>

LOG_MODULE_REGISTER(buzzer, LOG_LEVEL_INF);

static const struct device *buzzer_dev;

int buzzer_init(void)
{
    buzzer_dev = device_get_binding("GPIO_0");
    return gpio_pin_configure(buzzer_dev, 3, GPIO_OUTPUT);
}

void buzzer_start(void)
{
    gpio_pin_set(buzzer_dev, 3, 1);
}

void buzzer_stop(void)
{
    gpio_pin_set(buzzer_dev, 3, 0);
}
