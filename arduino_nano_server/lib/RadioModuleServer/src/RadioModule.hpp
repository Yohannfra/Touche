#ifndef RADIOMODULE_HPP
#define RADIOMODULE_HPP

#include <Arduino.h>
#include <SPI.h>
#include "protocol.h"

class RadioModule
{
private:
    // NRF24 nrf24;
public:
    RadioModule();
    void init();
    packet_t receiveMsg();
};

#endif /* RADIOMODULE_HPP */