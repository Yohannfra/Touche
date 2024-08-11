/*
Touché Project
Copyright (C) 2024 Assouline Yohann

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

#include "protocol.h"

#include <Arduino.h>
#include <RF24.h>

class RadioModule {
  private:
    RF24 _nrf24;
    touche_role_e _role;
    ack_payload_t _ackPayload;

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
    void init(touche_role_e role);

    /**
    * @brief check if a message is available and reads it
    *
    * @param ack ack message to send back to the sender
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
    * @param payload payload to send
    *
    * @return the ACK received
    */
    ack_payload_t sendMsg(payload_type_e payload);

    void setAckPayload(uint8_t newAck);
};

#endif /* RADIOMODULE_HPP */
