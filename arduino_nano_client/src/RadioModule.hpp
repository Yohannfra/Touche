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
        void sendMsg();
};

#endif /* RADIOMODULE_HPP */