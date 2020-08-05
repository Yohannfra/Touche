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
#include "client.h"

static esp_now_peer_info_t peer;

static void wifi_init()
{
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

static void espnow_send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (mac_addr == NULL) {
        ESP_LOGI("Client", "Send callback arg error");
        return;
    }
    ESP_LOGI("Client", "\r\nLast Packet Send Status:\t");
    ESP_LOGI("Client", "%s\n",
        status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void my_espnow_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase() );
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_init(); // Wifi must be started before esp_now

    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_send_cb(espnow_send_cb));

    memcpy(peer.peer_addr, SERVER_MAC_ADDR, 6 * sizeof(uint8_t));
    peer.channel = 0;
    peer.encrypt = false;
    esp_now_add_peer(&peer);
}

static void my_espnow_send_message(message_t *message)
{
    esp_err_t result = esp_now_send(
            SERVER_MAC_ADDR,
            (uint8_t *)message,
            sizeof(message));

    if (result == ESP_OK) {
        ESP_LOGI("Client", "Sent with success");
    } else {
        ESP_LOGI("Client", "Error sending the data : %s", esp_err_to_name(result));
    }
}

void my_espnow_send_hit(void)
{
    message_t message;

    message.index_sender = 0;
    message.capsensValue = -1;
    message.payload = HIT;
    ESP_LOGI("Client", "Sending hit...");
    my_espnow_send_message(&message);
}

void my_espnow_send_ground(void)
{
    message_t message;

    message.index_sender = 0;
    message.capsensValue = -1;
    message.payload = GROUND;
    ESP_LOGI("Client", "Sending ground...");
    my_espnow_send_message(&message);
}