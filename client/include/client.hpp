/*
** Assouline Yohann, 2020
** WSSF
** File description:
** client header
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "constants.hpp"

typedef struct message_s {
    uint8_t id_sender[];
    payload_types_e payload;
}   message_t;

// utils.ino
void handle_error();
void blink_led(byte pin);

#endif // CLIENT_HPP
