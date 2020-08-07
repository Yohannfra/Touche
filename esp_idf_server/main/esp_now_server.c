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
#include "server.h"

static message_t message;
static unsigned long player_ground_touched[2] = {0, 0};
static uint8_t client_mac_addr[2][6] = {{0}, {0}};

extern int64_t time_last_hit;
extern payload_types_e player_hit[2];

#define GET_OPPONENT(id) (id == PLAYER_1) ? PLAYER_2 : PLAYER_1

void wifi_init()
{
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

static void hit(int player_id)
{
    // If a player touched but the the opponent's ground got triggered before
    if (player_ground_touched[GET_OPPONENT(player_hit)] &&
            player_ground_touched[GET_OPPONENT(player_hit)] - esp_timer_get_time() < FENCING_LAPS_GROUND_NO_TOUCH) {
        player_hit[player_id] = GROUND;
        player_ground_touched[GET_OPPONENT(player_hit)] = 0;
        return;
    } else { // Not sure abt this one
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
    if (player_ground_touched[player_id] == 0) {
        player_ground_touched[player_id] = esp_timer_get_time();
    }
}

static void print_recvd_msg(message_t *message, int player_id)
{
    ESP_LOGI("Server", "Message received: ");
    ESP_LOGI("Server", "Payload %s",
        message->payload == HIT ? "HIT" : \
        message->payload == GROUND ? "GROUND" : \
        message->payload == NONE ? "NONE" : "ERROR");
    ESP_LOGI("Server", "capsensValue : %d", message->capsensValue);
    ESP_LOG_BUFFER_HEX("Server", message->sender_mac_addr, sizeof(uint8_t[6]));
    ESP_LOGI("Server", "Player id is : %d", player_id);
}

int register_mac_addr(uint8_t sender_mac_addr[6])
{
    if (CMP_MAC_ADDR(client_mac_addr[PLAYER_1], UNITIALIZED_MAC_ADDR) == 0) {
        memcpy(client_mac_addr[PLAYER_1], sender_mac_addr, sizeof(uint8_t[6]));
        return PLAYER_1;
    }
    if (CMP_MAC_ADDR(client_mac_addr[PLAYER_1], sender_mac_addr) == 0)
        return PLAYER_1;

    if (CMP_MAC_ADDR(client_mac_addr[PLAYER_2], UNITIALIZED_MAC_ADDR) == 0) {
        memcpy(client_mac_addr[PLAYER_2], sender_mac_addr, sizeof(uint8_t[6]));
        return PLAYER_2;
    }
    if (CMP_MAC_ADDR(client_mac_addr[PLAYER_2], sender_mac_addr) == 0)
        return PLAYER_2;
    abort(); // UNKNOWN THIRD ADDRESS, FIX LATER WITH IDK WHAT YET
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message_t));

    int player_id = register_mac_addr(message.sender_mac_addr);
    print_recvd_msg(&message, player_id);

    switch (message.payload) {
        case HIT:
            hit(player_id);
            break;
        case GROUND:
            ground_touched(player_id);
            ESP_LOGI("Server", "Capsens value: %d ", message.capsensValue);
            break;
        case NONE: // Should not happend, just the value set on init
            break;
        case ERROR:
            break; // TODO : error handling or stuff
    }
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
