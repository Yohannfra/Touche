#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "RadioModule.hpp"

#include <Arduino.h>

#include "protocol.h"
#include "fencingConstants.h"

#define BUZZER_PIN 10
#define LED_RING_PIN 3

Buzzer buzzer(BUZZER_PIN);
LedRing led_ring(LED_RING_PIN);
RadioModule radio_module;

device_id_t knowns_ids[2] = {0, 0};

void setup()
{
    Serial.begin(9600);

    while (!Serial) {
        ; // wait for serial
    }
    radio_module.init();
    led_ring.init();
}

void register_player(int8_t id)
{
    if (knowns_ids[0] == 0) { // register player 1
        knowns_ids[0] = id;
        led_ring.blink(RED_RGB, 200);
    } else if (knowns_ids[1] == 0) { // register player 2
        knowns_ids[1] = id;
        led_ring.blink(GREEN_RGB, 200);
    } else { // UNKNOWN ID
        Serial.print("UNKNOWN ID: ");
        Serial.println(id);
    }
}

unsigned long time_last_hit = 0;
bool player_hit[2] = {false, false};
device_id_t id_last_hit = 0;

void hit(uint8_t id)
{
    int64_t current_time = millis();

    if (time_last_hit == 0) { // first hit
        time_last_hit = millis();
        player_hit[id -1] = true;
    } else {
        if (current_time - time_last_hit <= FENCING_LAPS_DOUBLE_TOUCH) {
            player_hit[id - 1] = true;
        }
    }
}

void loop()
{
    packet_t packet = radio_module.receiveMsg();

    if (packet) {
        Serial.print("Received: ");
        Serial.println(packet);

        device_id_t id = GET_ID(packet);

        if (id != knowns_ids[0] && id != knowns_ids[1]) {
           register_player(id);
            return;
        }

        if (IS_HIT(packet)) {
            hit(id);
        } else if (IS_GND(packet)) {
            // TODO
        }
    }

    if (player_hit[0] || player_hit[1]) {
        buzzer.play();
        if (player_hit[0] && player_hit[1]) {
            led_ring.set_half_colors(RED_RGB, GREEN_RGB);
        } else if (player_hit[0]) {
            led_ring.set_color(GREEN_RGB);
        } else if (player_hit[1]) {
            led_ring.set_color(RED_RGB);
        }
    }

    if (millis() - time_last_hit > FENCING_BLINKING_TIME) { // time's up, reset all states
        player_hit[0] = false;
        player_hit[1] = false;
        time_last_hit = 0;
        led_ring.turn_off();
        buzzer.stop();
    }
}