
#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "RadioModule.hpp"
#include "PlayerManager.hpp"
#include "ActionManager.hpp"
#include <Arduino.h>

#include "protocol.h"
#include "fencingConstants.h"
#include "DebugLog.hpp"

#include "server_config.h"

Buzzer buzzer(BUZZER_PIN);
LedRing led_ring(LED_RING_PIN);
RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
PlayerManager player_manager;
ActionManager action_manager;

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
#endif
    radio_module.init();
    led_ring.init();
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

        DEBUG_LOG_VAL("Received: ", packet);

        device_id_t player_id = GET_ID(packet);
        player_index_e player_index = player_manager.getPlayerFromID(player_id);
        payload_type_e payload = (payload_type_e)((uint8_t)packet);

        DEBUG_LOG_VAL("id: ", player_id);
        DEBUG_LOG_VAL("index: ", player_index);

        if (player_index == NOT_A_PLAYER && player_manager.getPlayerCount() < 2) {
            player_index_e index = player_manager.registerPlayer(player_id);
            if (index != NOT_A_PLAYER) {
                led_ring.blink((index == PLAYER_1 ? RED_RGB : GREEN_RGB), 200, 3,
                    (player_manager.getPlayerCount() - 1) * NEOPIXEL_RING_SIZE);
                radio_module.clearReceiver();
            }
            return; // no hit on register
        }

        switch (payload)
        {
        case HIT:
            DEBUG_LOG_LN("HIT");
            action_manager.hit(player_index);
            break;
        case CALIBRATION_STARTING:
            DEBUG_LOG_LN("CALIBRATION STARTED");
            led_ring.do_circle_annimation(ORANGE_RGB);
            break;
        case CALIBRATION_END:
            DEBUG_LOG_LN("CALIBRATION END");
            led_ring.blink(GREEN_RGB, 100, 5);
            break;
        case CALIBRATION_FAILED:
            DEBUG_LOG_LN("CALIBRATION FAILED");
            led_ring.blink(RED_RGB, 100, 5);
            break;
        default:
            break;
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
