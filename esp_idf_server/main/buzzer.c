#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "server.h"
#include "constants.h"

void init_buzzer(int pin)
{
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_DISABLE; // disable interupt
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = pin;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}

void playBuzzer(void)
{
    gpio_set_level(BUZZER_GPIO, 1);
}

void stopBuzzer(void)
{
    gpio_set_level(BUZZER_GPIO, 0);
}