#ifndef CONFIG_H
#define CONFIG_H

// ------ Config ------------

// Change that to 1 if you want to change a board from PLAYER_1 to PLAYER_2
// but reflash with 0 after doing so (to preserve EEPROM)
#define FORCE_WRITE_PLAYER_ROLE 0

#define PLAYER_ROLE PLAYER_1 // change value to PLAYER_1 or PLAYER_2

// ------ Pinout ------------

/**
 * @brief Arduino pin used for the led
 */
#define LED_PIN_RED 10
#define LED_PIN_GREEN 9
#define LED_PIN_BLUE 6

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

#endif // CONFIG_H