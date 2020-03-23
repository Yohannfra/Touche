#include <WiFi.h>
#include <esp_now.h>

// server

// esp2

typedef struct message_s {
    byte id_sender;
    byte payload;
} message_t;

message_t message;

const byte LED_CONNECTED_1 = 14;
const byte LED_CONNECTED_2 = 27;
const byte LED_TOUCH_1= 12;
const byte LED_TOUCH_2= 26;

void blink_led(byte pin)
{
    digitalWrite(pin, HIGH);
    delay(1000);
    digitalWrite(pin, LOW);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message_t));
    if (message.payload == 1) {
        if (message.id_sender == 1) {
            blink_led(LED_TOUCH_1);
        } else {
            blink_led(LED_TOUCH_1);
        }
    }
}

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv);
    pinMode(LED_TOUCH_1, OUTPUT);
    pinMode(LED_TOUCH_2, OUTPUT);
    pinMode(LED_CONNECTED_1, OUTPUT);
    pinMode(LED_CONNECTED_2, OUTPUT);
}

void loop()
{
}
