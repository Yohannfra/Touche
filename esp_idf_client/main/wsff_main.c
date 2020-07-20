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

void restart_board(void)
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

void send_message(message_t *message)
{
    esp_err_t result = esp_now_send(
            MAC_ADDR_LIST[SERIAL_ID][SERVER_MAC_ADDR_INDEX],
            (uint8_t *)message,
            sizeof(message));

    if (result == ESP_OK) {
        ESP_LOGI("Client", "Sent with success");
    } else {
        ESP_LOGI("Client", "Error sending the data : %s", esp_err_to_name(result));
    }
}

void send_hit(void)
{
    message_t message;

    message.index_sender = 0;
    message.capsensValue = -1;
    message.payload = HIT;
    ESP_LOGI("Client", "Sending hit...");
    send_message(&message);
}

void send_ground(void)
{
    ESP_LOGI("Client", "Sending ground...");
    // TODO
    ESP_LOGI("Client", "Done.");
}

void init_captouch(void)
{
    // TODO
}

int get_captouch(int gpio)
{
    (void)gpio;

    return 0;
}

void app_main()
{
    print_chip_infos();
    init_gpios();
    init_esp_now();
    init_captouch();

    ESP_LOGI("Client", "Init Done. Starting the main loop");

    while (true) {
        if (gpio_get_level(BUTTON_GPIO)) {
            send_hit();
            gpio_set_level(LED_GPIO, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_set_level(LED_GPIO, 0);
        }
        // recup la value capsens ...
        int captouch_value = get_captouch(GROUND_GPIO);
        if (captouch_value > GROUND_VALUE_CAPSENS_EPEE) {
            send_ground();
        }
        // leave time for other tasks in FreeRTOS
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
