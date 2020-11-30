#include "RadioModule.hpp"

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include "protocol.h"
#include "utils.hpp"

RF24 radio(7,8);

const uint64_t pipe = 0xE8E8F0F0E1LL;

RadioModule::RadioModule()
{

}

void RadioModule::init()
{
    radio.begin();

    if (radio.isChipConnected()) {
        Serial.println("Connected");
    } else {
        Serial.println("Connection Error");
    }
    radio.openWritingPipe(pipe);
    radio.openReadingPipe(1,pipe);
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
}

void RadioModule::sendMsg(int8_t id, int8_t type)
{
    packet_t packet = 0;

    packet |= (id << 3);
    packet |= type;

    #if 0
    utils::print_bin("id", id);
    utils::print_bin("type", type);
    utils::print_bin("packet", packet);
    #endif

    bool ack = radio.write(&packet, sizeof(packet));

    if (ack) {
        Serial.println("ACK received");
    } else {
        Serial.println("ACK not received");
    }
}