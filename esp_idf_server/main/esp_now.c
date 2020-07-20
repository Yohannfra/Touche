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

static message_t message;
static unsigned long player_ground_touched[2] = {0, 0};

extern time_t time_last_hit;
extern bool player_hit[2];
/* extern LedRing ledRingP1; */
/* extern LedRing ledRingP2; */

#define GET_OPPONENT(id) (id == PLAYER_1) ? PLAYER_1 : PLAYER_2

void wifi_init()
{
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

#if CONFIG_ESPNOW_ENABLE_LONG_RANGE
    ESP_ERROR_CHECK(esp_wifi_set_protocol(ESPNOW_WIFI_IF, WIFI_PROTOCOL_11B|WIFI_PROTOCOL_11G|WIFI_PROTOCOL_11N|WIFI_PROTOCOL_LR));
#endif
}

static void hit(int player_id)
{
    // If a player touched but the the opponent's ground got triggered before
    if (player_ground_touched[GET_OPPONENT(player_hit)] - esp_timer_get_time() < FENCING_LAPS_GROUND_NO_TOUCH) {
        player_hit[player_id] = GROUND;
        player_ground_touched[GET_OPPONENT(player_hit)] = 0;
        return;
    } else { // should not happend but error handling
        player_ground_touched[GET_OPPONENT(player_hit)] = 0;
    }

    if (time_last_hit == 0) {
        time_last_hit = esp_timer_get_time();
        player_hit[player_id] = HIT;
    } else {
        if (esp_timer_get_time() - time_last_hit <= FENCING_LAPS_DOUBLE_TOUCH) {
            player_hit[player_id] = HIT;
        }
    }
}

static void ground_touched(int player_id)
{
    if (player_ground_touched[player_id] == 0)
        player_ground_touched[player_id] = esp_timer_get_time();
#ifdef DEBUG
    ledRingP1.setAllColors(ORANGE);
    ledRingP2.setAllColors(ORANGE);
    delay(500);
    ledRingP1.turnOff();
    ledRingP2.turnOff();
#endif
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message_t));
    ESP_LOGI("Server", "Message received: ");
    ESP_LOGI("Server", "%s", message.payload == HIT ? "HIT\n" : "GROUND\n");

    switch (message.payload) {
        case HIT:
            hit(message.index_sender - 1);
            break;
        case GROUND:
            ground_touched(message.index_sender - 1);
            ESP_LOGI("Server", "Capsens value: %d ", message.capsensValue);
            break;
        case NONE: // Should not happend
            break;
        case ERROR:
            break; // TODO : error handling or stuff
    }
}

void init_esp_now()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase() );
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_init(); // Wifi must be started before esp_now
    //
    // Initialize ESPNOW and register sending and receiving callback function.
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(OnDataRecv));
}
