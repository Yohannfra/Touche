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
#include "my_esp_now.h"
#include "captouch.h"

void init_gpios(void)
{
    gpio_config_t io_conf;

    // LED GPIO
    io_conf.intr_type = GPIO_INTR_DISABLE; // disable interupt
    io_conf.mode = GPIO_MODE_OUTPUT; // output gpio
    io_conf.pin_bit_mask = LED_GPIO_BM; // the pin bitmask
    io_conf.pull_down_en = 0; //disable pull-down mode
    io_conf.pull_up_en = 0; //disable pull-up mode
    gpio_config(&io_conf);

    // BUTTON GPIO
    io_conf.intr_type = GPIO_INTR_ANYEDGE; // Enable interrupt on both rising and falling edges
    io_conf.mode = GPIO_MODE_INPUT;               // Set as Input
    io_conf.pin_bit_mask = BUTTON_GPIO_BM; // Bitmask
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;     // Disable pullup
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;  // Enable pulldown
    gpio_config(&io_conf);
}
void task_button_pressed(void *pvParameter);

void app_main()
{
    print_chip_infos();
    init_gpios();
    init_esp_now();
    init_captouch(GROUND_GPIO);

    ESP_LOGI("Client", "Creating the button task.");
    xTaskCreate(&task_button_pressed, "buttonPressed", 2048, NULL, 5, NULL);

    ESP_LOGI("Client", "Creating the esp now task");
    // xtask create for espnow

    // while (true) {
    //     if (gpio_get_level(BUTTON_GPIO)) {
    //         send_hit();
    //         gpio_set_level(LED_GPIO, 1);
    //         vTaskDelay(1000 / portTICK_PERIOD_MS);
    //         gpio_set_level(LED_GPIO, 0);
    //     }
    //     // recup la value capsens ...
    //     int captouch_value = get_captouch(GROUND_GPIO);
    //     if (captouch_value > GROUND_VALUE_CAPSENS_EPEE) {
    //         send_ground();
    //     }
    //     // leave time for other tasks in FreeRTOS
    //     vTaskDelay(10 / portTICK_PERIOD_MS);
    // }
}
