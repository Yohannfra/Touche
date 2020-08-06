#include "client.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include <esp_log.h>
#include <stdio.h>
#include "my_esp_now.h"

static int hit_recvd = 0;

void isr_button_pressed(void *args)
{
    bool btn_state = (bool)gpio_get_level(BUTTON_GPIO);
    hit_recvd = btn_state;
}

void task_button_pressed(void *pvParameter)
{
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_GPIO, isr_button_pressed, NULL);
    ESP_LOGI("Client", "Interrupt configured\n");

    while (1) {
        // ESP_LOGI("Client", "Waiting for button press....");
        if (hit_recvd) {
            gpio_set_level(LED_GPIO, true);
            my_espnow_send_hit();
            hit_recvd = 0;
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_set_level(LED_GPIO, false);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}