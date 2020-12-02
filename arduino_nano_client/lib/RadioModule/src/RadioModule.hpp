#ifndef RADIOMODULE_HPP
#define RADIOMODULE_HPP

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

class RadioModule
{
    private:
        RF24 _radio;
    public:
        RadioModule(uint16_t cePin, uint16_t csPin);
        void init();
        void sendMsg(int8_t id, int8_t type);
};

#endif /* RADIOMODULE_HPP */