#include "RadioModule.hpp"

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include "protocol.h"

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

    packet |= id;
    packet |= type;
    bool ack = radio.write(&packet, sizeof(packet));

    // Serial.print("Sent: ");
    // Serial.println(rxTxData);

    if (ack) {
        Serial.println("ACK received");
    } else {
        Serial.println("ACK not received");
    }
}