#include "client.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include <esp_log.h>
#include <stdio.h>

void isr_button_pressed(void *args)
{
    int btn_state = gpio_get_level(BUTTON_GPIO);
    gpio_set_level(LED_GPIO, btn_state);
    // ESP_LOGI("Client", "HIT !");
    gpio_set_level(LED_GPIO, 1);
            // vTaskDelay(1000 / portTICK_PERIOD_MS);
            // gpio_set_level(LED_GPIO, 0);
}

void task_button_pressed(void *pvParameter)
{
    // Configure interrupt and add handler
    gpio_install_isr_service(0); // Start Interrupt Service Routine service
    gpio_isr_handler_add(BUTTON_GPIO, isr_button_pressed, NULL);
    ESP_LOGI("Client", "Interrupt configured\n");

    // Wait
    while (1) {
        ESP_LOGI("test", "Waiting for button press....");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}