#include "RadioModule.hpp"
#include "DebugLog.hpp"
#include "protocol.h"

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#define PIPE_PLAYER_1 1
#define PIPE_PLAYER_2 2

static const uint64_t PIPES_ADDRESSES[2] = {
    0xB3B4B5B601LL,
    0xB3B4B5B602LL
};

RadioModule::RadioModule(uint16_t cePin, uint16_t csPin) : _nrf24(cePin, csPin)
{
}

void RadioModule::init(wsff_role_e role)
{
    _nrf24.begin();

    if (_nrf24.isChipConnected()) {
        DEBUG_LOG_LN("Connected to NRF24L01");
    } else {
        DEBUG_LOG_LN("Error connecting to NRF24L01");
    }

    _nrf24.setDataRate(RF24_250KBPS);
    _nrf24.setPALevel(RF24_PA_MAX);
    _nrf24.setPayloadSize(sizeof(packet_t));

    if (role == PLAYER_1 || role == PLAYER_2) {
        _nrf24.stopListening(); // put radio in TX mode
        _nrf24.openWritingPipe(PIPES_ADDRESSES[role]);
        _nrf24.setRetries(3 + (role == PLAYER_2), 15);
    } else if (role == SERVER) {
        _nrf24.openReadingPipe(PIPE_PLAYER_1, PIPES_ADDRESSES[PLAYER_1]);
        _nrf24.openReadingPipe(PIPE_PLAYER_2, PIPES_ADDRESSES[PLAYER_2]);
        _nrf24.startListening();
    }

    DEBUG_LOG_LN("NRF24l01 Initialized");
}

#if defined(WSFF_SERVER)

bool RadioModule::checkMsgAvailable()
{
    return _nrf24.available();
}

packet_t RadioModule::receiveMsg()
{
    packet_t packet;

    if (_nrf24.available()) {
        _nrf24.read(&packet, sizeof(packet_t));
        return packet;
    }
    return 0;
}

void RadioModule::clearReceiver()
{
    _nrf24.flush_rx();
}

#elif defined(WSFF_CLIENT)

void RadioModule::sendMsg(wsff_role_e role, payload_type_e payload)
{
    packet_t packet = 0;

    packet |= payload;

    if (role == PLAYER_1) {
        packet |= BIT_MASK_ID_PLAYER_1;
    } else if (role == PLAYER_2) {
        packet |= BIT_MASK_ID_PLAYER_2;
    }

    #if 0
    utils::print_bin("type", type);
    utils::print_bin("packet", packet);
    #endif

    bool ack = _nrf24.write(&packet, sizeof(packet));
    if (ack) {
        DEBUG_LOG_LN("ACK received");
    } else {
        DEBUG_LOG_LN("ACK not received");
    }
}

#endif