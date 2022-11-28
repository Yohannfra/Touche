/*
Touché Project
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

#include "RadioModule.hpp"

#include "ArduinoLog.h"
#include "protocol.h"
#include "radioPipes.h"
#include "utils.hpp"

#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>

#define PIPE_PLAYER_1 1
#define PIPE_PLAYER_2 2

RadioModule::RadioModule(uint16_t cePin, uint16_t csPin) : _nrf24(cePin, csPin), _ackPayload(0)
{
}

void RadioModule::init(touche_role_e role)
{
    _nrf24.begin();
    _role = role;

    if (_nrf24.isChipConnected()) {
        Log.notice("Connected to NRF24L01");
    } else {
        Log.error("Error connecting to NRF24L01");
    }

    // Low data rate and maximum PALevel for best range possible
    _nrf24.setDataRate(RF24_250KBPS);
    _nrf24.setPALevel(RF24_PA_MAX);

    _nrf24.setPayloadSize(sizeof(packet_t));

    // to have different retries delay on players
    _nrf24.setRetries(3 + (_role == PLAYER_2), 15);

    // enable custom ack payload
    // to use ACK payloads, we need to enable dynamic payload lengths
    _nrf24.enableDynamicPayloads();
    _nrf24.enableAckPayload();

    if (_role == PLAYER_1 || _role == PLAYER_2) {
        _nrf24.openReadingPipe(0, PIPES_ADDRESSES[_role]);
        _nrf24.stopListening();  // put radio in TX mode
        _nrf24.openWritingPipe(PIPES_ADDRESSES[_role]);
    } else if (_role == SERVER) {
        _nrf24.openReadingPipe(PIPE_PLAYER_1, PIPES_ADDRESSES[PLAYER_1]);
        _nrf24.openReadingPipe(PIPE_PLAYER_2, PIPES_ADDRESSES[PLAYER_2]);
        _nrf24.openWritingPipe(PIPE_PLAYER_1);
        _nrf24.openWritingPipe(PIPE_PLAYER_2);
        _nrf24.startListening();  // put in RX
    }

    Log.notice("NRF24l01 Initialized");
}

bool RadioModule::checkMsgAvailable()
{
    return _nrf24.available();
}

packet_t RadioModule::receiveMsg()
{
    packet_t packet;

    uint8_t pipe = 0;
    if (_nrf24.available(&pipe)) {
        // send ack
        ack_payload_t ackPayload = _ackPayload;
        _nrf24.writeAckPayload(pipe, &ackPayload, sizeof(ack_payload_t));

        // read data
        _nrf24.read(&packet, sizeof(packet_t));
        return packet;
    }
    return 0;
}

ack_payload_t RadioModule::sendMsg(payload_type_e payload)
{
    packet_t packet = CREATE_PACKET(_role, payload);

#if 0
        utils::print_packet(packet);
#endif

    _nrf24.write(&packet, sizeof(packet));

    // read ack payload
    ack_payload_t ack = ACK_ERROR;
    if (_nrf24.available()) {
        Log.notice("Reading ack....");
        _nrf24.read(&ack, sizeof(ack_payload_t));
    }

    return ack;
}

void RadioModule::setAckPayload(uint8_t newAck)
{
    _ackPayload = newAck;
    Log.notice("New ack payload set:");
    utils::print_ack_payload(_ackPayload);
}
