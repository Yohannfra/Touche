/*
WSFF Project
Copyright (C) 2021 Assouline Yohann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RADIOMODULE_HPP
#define RADIOMODULE_HPP

#include <Arduino.h>
#include "protocol.h"
#include <RF24.h>

typedef enum : uint8_t {
    RECEIVER,
    SENDER
} radio_module_mode_e;

class RadioModule
{
    private:
        RF24 _nrf24;
        radio_module_mode_e _mode;

    public:
        /**
         * @brief Construct a new Radio Module object
         *
         * @param cePin The pin attached to Chip Enable on the RF module
         * @param csPin The pin attached to Chip Select
         */
        RadioModule(uint16_t cePin, uint16_t csPin);

        /**
         * @brief initialize the RF module
         *
         * @param role device role enum
         */
        void init(wsff_role_e role);

        /**
         * @brief check if a message is available and reads it
         *
         * @return packet_t a packet_t structure if a message has been read or 0
         */
        packet_t receiveMsg();

        /**
         * @brief check if a message is available
         *
         * @return true a message is available
         * @return false no message available
         */
        bool checkMsgAvailable();

        /**
         * @brief send a message in a packet_t
         *
         * @param role device role enum
         * @param payload payload to send
         *
         * @return If an ACK was received
         */
        bool sendMsg(wsff_role_e role, payload_type_e payload);

        void setMode(radio_module_mode_e mode);
};

#endif /* RADIOMODULE_HPP */