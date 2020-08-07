#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "esp_timer.h"

#include "driver/gpio.h"
#include "esp_now.h"
#include "esp_log.h"

#include "client.h"
#include "constants.h"
#include "esp_now_client.h"
#include "captouch.h"

int64_t time_since_last_action = 0;

void init_gpios(void)
{
    gpio_config_t io_conf;

    // deinit the button used for wake from sleep
    rtc_gpio_deinit(BUTTON_GPIO); // TODO check if it works

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
void sleep_handle_task(void *pvParameter);

void app_main()
{
    init_gpios();
    my_espnow_init();
    captouch_init();
    esp_timer_init();

    // init for deep sleep
    esp_sleep_enable_ext1_wakeup(BUTTON_GPIO_BM, ESP_EXT1_WAKEUP_ANY_HIGH);

    // Blink led at the end of init
    gpio_set_level(LED_GPIO, true);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(LED_GPIO, false);

    xTaskCreate(&task_button_pressed, "buttonPressed", 2048, NULL, 5, NULL);
    xTaskCreate(&captouch_read_task, "captouchRead", 2048, NULL, 5, NULL);
    xTaskCreate(&sleep_handle_task, "sleepHandler", 2048, NULL, 5, NULL);
}
