#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H

#ifdef WRITE_ROLE_TO_EEPROM
#define ROLE_TO_WRITE PLAYER_1 // change value to PLAYER_1 or PLAYER_2
#endif

/**
 * @brief How long the button must be pressed (and maintened) to start calibration
 */
#define TIME_TO_ACTIVATE_CALIBRATION 2000 // 2 seconds

/**
 * @brief Arduino pin used for the led
 */
#define LED_PIN_RED 10
#define LED_PIN_GREEN 6
#define LED_PIN_BLUE 9

/**
 * @brief Arduino pin for the button of the weapon
 */
#define EPEE_BUTTON_PIN 3

/**
 * @brief Arduino pin for chip enable pin of NRF24L01
 */
#define NRF24L01_CE_PIN 7

/**
 * @brief Arduino pin for chip select pin of NRF24L01
 */
#define NRF24L01_CS_PIN 8

/**
 * @brief Arduino pin for capacitive sensor in
 */
#define VIRTUAL_PIN_IN 2

/**
 * @brief Arduino pin for capacitive sensor out
 */
#define VIRTUAL_PIN_OUT 4

#endif // CLIENT_CONFIG_H
