#include <esp_now.h>
#include <WiFi.h>

// client

// esp1
uint8_t broadcastAddress[] = {0x24, 0x62, 0xAB, 0xB0, 0x73, 0x50}; // esp2

typedef struct message_s {
    byte id_sender;
    byte payload;
}   message_t;

message_t message;

const byte BUTTON_PIN = 17;
const byte LED_PIN = 16;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void blink_led(byte pin)
{
    digitalWrite(pin, HIGH);
    delay(1000);
    digitalWrite(pin, LOW);
}

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_register_send_cb(OnDataSent);

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }
    message.id_sender = 1;
    message.payload = 1;

    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void send_message()
{
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &message, sizeof(message_t));

    if (result == ESP_OK) {
        Serial.println("Sent with success");
    }
    else {
        Serial.println("Error sending the data");
    }
}

void loop()
{
    if (digitalRead(BUTTON_PIN)) {
        send_message();
        blink_led(LED_PIN);
    }
}
