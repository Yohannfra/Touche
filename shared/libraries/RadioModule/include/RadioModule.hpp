#ifndef RADIOMODULE_HPP
#define RADIOMODULE_HPP

#include <Arduino.h>
#include "protocol.h"
#include <RF24.h>

class RadioModule
{
    private:
        RF24 _nrf24;

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
         * @brief clear the message queue
         *
         */
        void clearReceiver();

        /**
         * @brief send a message in a packet_t
         *
         * @param role device role enum
         * @param payload payload to send
         */
        void sendMsg(wsff_role_e role, payload_type_e payload);
};

#endif /* RADIOMODULE_HPP */