#include "RadioModule.hpp"
#include "DebugLog.hpp"
#include "protocol.h"

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

RadioModule::RadioModule(uint16_t cePin, uint16_t csPin) : _nrf24(cePin, csPin)
{
}

void RadioModule::init()
{
    _nrf24.begin();

    if (_nrf24.isChipConnected()) {
        DEBUG_LOG_LN("Connected to NRF24L01");
    } else {
        DEBUG_LOG_LN("Error connecting to NRF24L01");
    }

#if defined(WSFF_CLIENT)
        _nrf24.openWritingPipe(NRF24_WSFF_PIPE);
#elif defined(WSFF_SERVER)
        _nrf24.openReadingPipe(1, NRF24_WSFF_PIPE);
#endif

    _nrf24.setDataRate(RF24_250KBPS);
    _nrf24.setPALevel(RF24_PA_MAX);

#ifdef WSFF_SERVER
    _nrf24.startListening();
#endif
    DEBUG_LOG_LN("NRF24l01 Initialized");
}

#if defined(WSFF_SERVER)

bool RadioModule::checkMsgAvailable()
{
    return _nrf24.available();
}

packet_t RadioModule::receiveMsg()
{
    packet_t t;

    if (_nrf24.available()) {
        _nrf24.read(&t, sizeof(t));
        return t;
    }
    return 0;
}

void RadioModule::clearReceiver()
{
    _nrf24.flush_rx();
}

#elif defined(WSFF_CLIENT)

void RadioModule::sendMsg(int8_t id, payload_type_e payload)
{
    packet_t packet = 0;

    packet |= (id << 8);
    packet |= payload;

    #if 0
    utils::print_bin("id", id);
    utils::print_bin("type", type);
    utils::print_bin("packet", packet);
    #endif

    uint8_t try_times = 0;
    const uint8_t MAX_TRY = 10; // number of times trying to send befor timeout
    do {
        bool ack = _nrf24.write(&packet, sizeof(packet));
        if (ack) {
            DEBUG_LOG_LN("ACK received");
            return;
        } else {
            DEBUG_LOG_LN("ACK not received");
        }
        try_times += 1;
    } while (try_times < MAX_TRY);
    DEBUG_LOG_LN("TIMEOUT: Couldn't send message");
}

#endif