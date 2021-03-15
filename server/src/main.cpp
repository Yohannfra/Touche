
#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "RadioModule.hpp"
#include "ActionManager.hpp"
#include <Arduino.h>

#include "protocol.h"
#include "fencingConstants.h"
#include "DebugLog.hpp"

#include "server_config.h"

#include "utils.hpp"

Buzzer buzzer(BUZZER_PIN);
LedRing led_ring(LED_RING_PIN);
RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
ActionManager action_manager;

static const wsff_role_e BOARD_ROLE = SERVER;

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
#endif
    radio_module.init(BOARD_ROLE);
    led_ring.init();

    led_ring.blink(ORANGE_RGB, 200, 1);
}

void resetValues()
{
    DEBUG_LOG_LN("resetting values");
    action_manager.reset();
    led_ring.turn_off();
    buzzer.stop();
}

void loop()
{
    packet_t packet = radio_module.receiveMsg();

    if (packet) {
        utils::print_packet(packet);

        wsff_role_e player_role = (wsff_role_e)GET_ROLE(packet);
        payload_type_e payload = (payload_type_e)packet;

        if (payload & HIT) {
            DEBUG_LOG_LN("HIT");
            action_manager.hit(player_role);
        } else if (payload & CALIBRATION_STARTING) {
            DEBUG_LOG_LN("CALIBRATION STARTED");
            for (size_t i = 0; i < NB_NEOPIXEL * 4; i++) {
                led_ring.do_circle_annimation(ORANGE_RGB, i);
                packet_t p = radio_module.receiveMsg();
                if (p) {
                    break;
                }
            }
            led_ring.turn_off();
        } else if (payload & CALIBRATION_END) {
            DEBUG_LOG_LN("CALIBRATION END");
            led_ring.blink(GREEN_RGB, 100, 3);
        } else if (payload & CALIBRATION_FAILED) {
            DEBUG_LOG_LN("CALIBRATION FAILED");
            led_ring.blink(RED_RGB, 100, 3);
        }
    }

    hit_type_e hit_type = action_manager.getHitStatus();

    if (hit_type != NO_HIT) {
        buzzer.play();
        led_ring.show_hits(hit_type);
    }
    if (action_manager.isResetTime()) {
        resetValues();
    }
}
