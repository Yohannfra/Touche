#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "constants.hpp"
#include "Utils.hpp"
#include <client.hpp>

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    printDebugLog("\r\nLast Packet Send Status:\t");
    printDebugLog(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success\n" : "Delivery Fail\n");
}

esp_err_t sendMessage(const message_t *message)
{
    esp_err_t result = esp_now_send(MAC_ADDR_LIST[SERIAL_ID][SERVER_MAC_ADDR_INDEX], (uint8_t *)message, sizeof(message_t));

    if (result == ESP_OK) {
        printDebugLog("Sent with success\n");
        return ESP_OK;
    } else {
        printDebugLog("Error sending the data\n");
        return ESP_FAIL;
    }
}

esp_err_t setupEspNow()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        printDebugLog("Error initializing ESP-NOW\n");
        return ESP_FAIL;
    }
    esp_now_register_send_cb(OnDataSent);

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, MAC_ADDR_LIST[SERIAL_ID][SERVER_MAC_ADDR_INDEX], 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    return esp_now_add_peer(&peerInfo);
}
