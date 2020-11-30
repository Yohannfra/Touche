#include "RadioModule.hpp"

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

// NRF24 my_nrf24;


RF24 my_nrf24(7, 8);

const uint64_t pipe = 0xE8E8F0F0E1LL;

RadioModule::RadioModule()
{

}

void RadioModule::init()
{
    my_nrf24.begin();
    if (my_nrf24.isChipConnected()) {
        Serial.println("Connected");
    } else {
        Serial.println("Connection Error");
    }
    my_nrf24.openReadingPipe(1,pipe);
    my_nrf24.openWritingPipe(pipe);
    my_nrf24.setDataRate(RF24_250KBPS);
    my_nrf24.setPALevel(RF24_PA_MIN);
    my_nrf24.startListening();
    Serial.print("Selected Power Level: ");
    Serial.println(my_nrf24.getPALevel());

    Serial.println("initialised");
}

packet_t RadioModule::receiveMsg()
{
    packet_t t;

    if (my_nrf24.available()) {
        my_nrf24.read(&t, sizeof(t));
        return t;
    }
    return 0;
}