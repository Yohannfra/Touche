#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "constants.hpp"
#include <client.hpp>

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void send_message(const message_t *message)
{
    esp_err_t result = esp_now_send(MAC_ADDR_LIST[SERIAL_ID][SERVER_MAC_ADDR_INDEX], (uint8_t *)message, sizeof(message_t));

    if (result == ESP_OK) {
        Serial.println("Sent with success");
    } else {
        Serial.println("Error sending the data");
    }
}

esp_err_t setup_esp_now()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return ESP_FAIL;
    }
    esp_now_register_send_cb(OnDataSent);

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, MAC_ADDR_LIST[SERIAL_ID][SERVER_MAC_ADDR_INDEX], 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    return esp_now_add_peer(&peerInfo);
}
