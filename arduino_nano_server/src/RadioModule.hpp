#ifndef RADIOMODULE_HPP
#define RADIOMODULE_HPP

#include <Arduino.h>
#include <SPI.h>

class RadioModule
{
private:
    // NRF24 nrf24;
public:
    RadioModule();
    void init();
    long receiveMsg();
};

#endif /* RADIOMODULE_HPP */