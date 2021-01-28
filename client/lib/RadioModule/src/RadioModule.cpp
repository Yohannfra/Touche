#include "RadioModule.hpp"

#include <nRF24L01.h>
#include <RF24_config.h>
#include <SPI.h>
#include "utils.hpp"
#include "DebugLog.hpp"

static const uint64_t pipe = 0xE8E8F0F0E1LL;

RadioModule::RadioModule(uint16_t cePin, uint16_t csPin) : _radio(cePin, csPin)
{
}

void RadioModule::init()
{
    _radio.begin();

    if (_radio.isChipConnected()) {
        DEBUG_LOG_LN("Connected");
    } else {
        DEBUG_LOG_LN("Connection Error");
    }
    _radio.openWritingPipe(pipe);
    _radio.openReadingPipe(1, pipe);
    _radio.setPALevel(RF24_PA_MAX);
    _radio.setDataRate(RF24_250KBPS);
}

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
        bool ack = _radio.write(&packet, sizeof(packet));
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
