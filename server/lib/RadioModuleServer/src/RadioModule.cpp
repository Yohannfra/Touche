#include "RadioModule.hpp"
#include "DebugLog.hpp"
#include "protocol.h"

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

// TODO : why is it in the global scope ?
RF24 my_nrf24(7, 8);

RadioModule::RadioModule()
{

}

void RadioModule::init()
{
    my_nrf24.begin();
    if (my_nrf24.isChipConnected()) {
        DEBUG_LOG_LN("Connected");
    } else {
        DEBUG_LOG_LN("Connection Error");
    }
    my_nrf24.openReadingPipe(1, NRF24_WSFF_PIPE);
    my_nrf24.openWritingPipe(NRF24_WSFF_PIPE);
    my_nrf24.setDataRate(RF24_250KBPS);
    my_nrf24.setPALevel(RF24_PA_MAX);
    my_nrf24.startListening();
    DEBUG_LOG_LN("initialised");
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

void RadioModule::clearReceiver()
{
    my_nrf24.flush_rx();
}