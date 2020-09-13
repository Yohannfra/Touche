#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "server.h"
#include "constants.h"

static bool buzzer_state = false;

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
    #if 1 // Just for debug, remove for real test
    gpio_set_level(BUZZER_GPIO, 1);
    #endif
    buzzer_state = true;
}

void stopBuzzer(void)
{
    gpio_set_level(BUZZER_GPIO, 0);
    buzzer_state = false;
}

bool is_buzzer_on(void)
{
    return buzzer_state;
}
