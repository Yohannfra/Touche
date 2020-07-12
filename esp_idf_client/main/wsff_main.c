#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "driver/gpio.h"
#include "esp_now.h"

#include "client.h"

void restart_board()
{
    printf("Restarting...\n");
    fflush(stdout);
    esp_restart();
}

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
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = BUTTON_GPIO_BM;
    io_conf.pull_down_en = 1;
    gpio_config(&io_conf);

    // GROUND GPIO
    // TODO init capsens
}

void app_main()
{
    print_chip_infos();
    init_gpios();
    init_esp_now();

    while (true) {
        if (gpio_get_level(BUTTON_GPIO)) {
            // send esp_now msg ....
            gpio_set_level(LED_GPIO, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_set_level(LED_GPIO, 0);
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
    }
}
