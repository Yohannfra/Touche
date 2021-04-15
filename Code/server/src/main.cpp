#include <Arduino.h>

#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "RadioModule.hpp"
#include "ActionManager.hpp"
#include "Button.hpp"
#include "protocol.h"
#include "wsff.h"
#include "DebugLog.h"
#include "config.h"
#include "utils.hpp"
#include "ServerConfig.hpp"

static Buzzer buzzer(BUZZER_PIN);
static LedRing led_ring(LED_RING_PIN);
static RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
static ActionManager action_manager;

static Button buttonPisteMode(PIN_BUTTON_PISTE_MODE);
static Button buttonSwitchPlayer(PIN_BUTTON_SWITCH_PLAYERS);
static Button buttonChangeWeapon(PIN_BUTTON_CHANGE_WEAPON);
static ServerConfig serverConfig(DEFAULT_WEAPON_MODE);

static bool pisteMode = false;
static weapon_mode_e weapon_mode;

void setup()
{
    #ifdef DEBUG
        Serial.begin(9600);
    #endif

    weapon_mode = serverConfig.getWeapon();
    DEBUG_LOG_LN(weapon_mode == EPEE ? "EPEE": "FOIL");

    radio_module.init(SERVER);
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

void checkButtonsPressed()
{
    // Piste mode
    if (buttonPisteMode.isPressed()) {
        DEBUG_LOG_LN("Button piste pressed !");
        pisteMode = !pisteMode;
        radio_module.sendMsg(SERVER, pisteMode ? ENABLE_PISTE_MODE : DISABLE_PISTE_MODE);
    }

    // switch players
    if (buttonSwitchPlayer.isPressed()) {
        DEBUG_LOG_LN("Button switch pressed !");
        led_ring.switchColors();
        led_ring.blinkBoth(led_ring.getPlayerColor(PLAYER_1), led_ring.getPlayerColor(PLAYER_2), 400, 2);
    }

    // change weapon
    if (buttonChangeWeapon.isPressed()) {
        DEBUG_LOG_LN("Button change weapon pressed !");
        weapon_mode = weapon_mode == EPEE ? FOIL : EPEE;
    }
}

void loop()
{
    packet_t packet = radio_module.receiveMsg();


    if (packet) {
        utils::print_packet(packet);

        wsff_role_e player_role = static_cast<wsff_role_e>(GET_ROLE(packet));
        payload_type_e payload = static_cast<payload_type_e>(GET_PAYLOAD(packet));

        if (payload & HIT) {
            DEBUG_LOG_LN("HIT");
            action_manager.hit(player_role);
        } else if (payload & CALIBRATION_STARTING) {
            DEBUG_LOG_LN("CALIBRATION STARTED");
            for (size_t i = 0; i < 2 * 4; i++) {
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

        if (action_manager.isResetTime()) {
            resetValues();
        }
    } else { // Check buttons only if no hit is occuring
        checkButtonsPressed();
    }
}
