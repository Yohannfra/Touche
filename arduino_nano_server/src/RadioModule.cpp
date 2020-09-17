#include "RadioModule.hpp"

RadioModule::RadioModule()
{
    if (!nrf24.init())
        Serial.println("NRF24 init failed");
}

/*
    see https://platformio.org/lib/show/42/nRF24
*/