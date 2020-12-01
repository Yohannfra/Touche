#ifndef RADIOMODULE_HPP
#define RADIOMODULE_HPP

#include <Arduino.h>
#include <SPI.h>

class RadioModule
{
    private:

    public:
        RadioModule();
        void init();
        void sendMsg(int8_t id, int8_t type);
};

#endif /* RADIOMODULE_HPP */