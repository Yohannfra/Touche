#ifndef RADIOMODULE_HPP
#define RADIOMODULE_HPP

#include <Arduino.h>
#include <NRF24.h>
#include <SPI.h>

class RadioModule
{
private:
    // NRF24 nrf24;
public:
    RadioModule();
    void init();
    void wait_for_message();
};

#endif /* RADIOMODULE_HPP */