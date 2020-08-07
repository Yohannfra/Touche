#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "driver/gpio.h"
#include "esp_now.h"
#include "esp_log.h"

#include "client.h"
#include "constants.h"
#include "esp_now_client.h"
#include "captouch.h"


void init_gpios(void)
{
    gpio_config_t io_conf;

    // LED GPIO
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = LED_GPIO_BM;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // BUTTON GPIO
    io_conf.intr_type = GPIO_INTR_ANYEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = BUTTON_GPIO_BM;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpio_config(&io_conf);
}

void task_button_pressed(void *pvParameter);
void captouch_read_task(void *pvParameter);

void app_main()
{
    init_gpios();
    my_espnow_init();
    captouch_init();

    xTaskCreate(&task_button_pressed, "buttonPressed", 2048, NULL, 5, NULL);
    xTaskCreate(&captouch_read_task, "captouchRead", 2048, NULL, 5, NULL);
}
