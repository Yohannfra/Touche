/*
** EPITECH PROJECT, 2020
** DefaultName
** File description:
** server
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include "constants.hpp"

typedef struct message_s {
    uint8_t id_sender[];
    payload_types_e payload;
}   message_t;


void blink_led(byte pin);

#endif // SERVER_HPP
