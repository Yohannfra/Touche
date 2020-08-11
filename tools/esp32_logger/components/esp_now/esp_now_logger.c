#include "esp_now.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_timer.h"

#include <stdio.h>
#include <string.h>

#include "constants.h"
#include <time.h>

static message_t message;

void wifi_init(void)
{
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

static void print_recvd_msg(message_t *msg)
{
    ESP_LOGI("Server", "Message received: ");
    ESP_LOGI("Server", "Payload %s",
        msg->payload == HIT ? "HIT" : \
        msg->payload == GROUND ? "GROUND" : \
        msg->payload == NONE ? "NONE" : "ERROR");
    ESP_LOGI("Server", "capsensValue : %d", msg->capsensValue);
    ESP_LOG_BUFFER_HEX("Server", msg->sender_mac_addr, sizeof(uint8_t[6]));
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message_t));

    print_recvd_msg(&message);
}

void init_esp_now(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase() );
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_init(); // Wifi must be started before esp_now

    // Initialize ESPNOW and register sending and receiving callback function.
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(OnDataRecv));
}
