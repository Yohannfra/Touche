#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "RadioModule.hpp"
#include "PlayerManager.hpp"

#include <Arduino.h>

#include "protocol.h"
#include "fencingConstants.h"
#include "DebugLog.hpp"

#define BUZZER_PIN 10
#define LED_RING_PIN 3

Buzzer buzzer(BUZZER_PIN);
LedRing led_ring(LED_RING_PIN);
RadioModule radio_module;
PlayerManager player_manager;

void setup()
{
    Serial.begin(9600);

    while (!Serial) {
        ; // wait for serial
    }
    radio_module.init();
    led_ring.init();
}

unsigned long time_last_hit = 0;
bool player_hit[2] = {false, false};

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

void resetValues()
{
    DEBUG_LOG("resetting values");
    player_hit[0] = false;
    player_hit[1] = false;
    time_last_hit = 0;
    led_ring.turn_off();
    buzzer.stop();
}

void loop()
{
    packet_t packet = radio_module.receiveMsg();

    if (packet) {
        DEBUG_LOG_VAL("Received: ", packet);

        device_id_t id = GET_ID(packet);

        if (player_manager.getPlayerFromID(id) == UNKNOWN_ID) {
            int8_t index = player_manager.registerPlayer(id);
            if (index != UNKNOWN_ID) {
                led_ring.blink(COLOR_CODE[index], 200);
            }
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

    if (time_last_hit && millis() - time_last_hit > FENCING_BLINKING_TIME) {
        resetValues();
    }
}