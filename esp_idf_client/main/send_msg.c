#include "esp_now.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

#include <stdio.h>
#include <string.h>

#include "constants.h"

static void send_message(message_t *message)
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
    message_t message;

    message.index_sender = 0;
    message.capsensValue = -1;
    message.payload = GROUND;
    ESP_LOGI("Client", "Sending ground...");
    send_message(&message);
}

