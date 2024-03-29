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
extern unsigned long player_ground_touched[2];
static uint8_t client_mac_addr[2][6] = {{0}, {0}};

extern int64_t time_last_hit;
extern payload_types_e player_hit[2];

#define GET_OPPONENT(id) (id == PLAYER_1) ? PLAYER_2 : PLAYER_1

#if EXTERNAL_ESP32_LOGGER
static esp_now_peer_info_t peer;
#endif

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

static void hit(int player_id)
{
    int64_t current_time = esp_timer_get_time();

    // If a player touched but the the opponent's ground got triggered before
    if (player_ground_touched[GET_OPPONENT(player_hit)] &&
            player_ground_touched[GET_OPPONENT(player_hit)] - current_time < FENCING_LAPS_GROUND_NO_TOUCH) {
        player_hit[player_id] = GROUND;
        player_ground_touched[GET_OPPONENT(player_hit)] = 0;
        time_last_hit = current_time;
        return;
    } else { // Not sure abt this one
        player_ground_touched[GET_OPPONENT(player_hit)] = 0;
    }

    if (time_last_hit == 0) {
        time_last_hit = current_time;
        player_hit[player_id] = HIT;
    } else {
        if (current_time - time_last_hit <= FENCING_LAPS_DOUBLE_TOUCH) {
            player_hit[player_id] = HIT;
        }
    }
}

static void ground_touched(int player_id)
{
    int64_t current_time = esp_timer_get_time();

    if (player_ground_touched[player_id] == 0 && time_last_hit == 0) { // ground sent first, easy case
        player_ground_touched[player_id] = current_time;
        player_hit[player_id] = GROUND;
        time_last_hit = current_time;
    } else if (player_ground_touched[player_id] == 0 && time_last_hit &&
        current_time - time_last_hit < TIME_BEFORE_SHOWING_HIT) {
        // eg. p1 touched p2 on gnd but the p1 msg arrived first
        if (player_hit[GET_OPPONENT(player_id) == HIT])
            player_hit[GET_OPPONENT(player_id)] = GROUND;
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

#if EXTERNAL_ESP32_LOGGER
    esp_err_t result = esp_now_send(EXTERNAL_LOGGER_MAC_ADDR,
        (uint8_t *)&message, sizeof(message_t));
    if (result == ESP_OK) {
        ESP_LOGI("Client", "Sent with success");
    } else {
        ESP_LOGI("Client", "Error sending the data : %s", esp_err_to_name(result));
    }
#endif

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

static void OnDataSend(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (mac_addr == NULL) {
        ESP_LOGI("Server", "Send callback arg error");
        return;
    }
    ESP_LOGI("Server", "\r\nLast Packet Send Status:\t");
    ESP_LOGI("Server", "%s\n",
        status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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
    ESP_ERROR_CHECK(esp_now_register_send_cb(OnDataSend));

#if EXTERNAL_ESP32_LOGGER
    memcpy(peer.peer_addr, EXTERNAL_LOGGER_MAC_ADDR, 6 * sizeof(uint8_t));
    peer.channel = 0;
    peer.encrypt = false;
    esp_now_add_peer(&peer);
#endif
}
