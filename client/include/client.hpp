/*
** Assouline Yohann, 2020
** WSSF
** File description:
** client header
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "constants.hpp"

#define BUTTON_PIN 17
#define LED_PIN 16

// utils.ino
void handle_error();
void blink_led(byte pin);

#endif // CLIENT_HPP
