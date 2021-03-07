#ifndef RADIOMODULE_HPP
#define RADIOMODULE_HPP

#include <Arduino.h>
#include "protocol.h"
#include <RF24.h>

class RadioModule
{
private:
    RF24 _nrf24;
public:
    RadioModule(uint16_t cePin, uint16_t csPin);
    void init();
    packet_t receiveMsg();
    bool checkMsgAvailable();
    void clearReceiver();
    void sendMsg(int8_t id, payload_type_e payload);
};

#endif /* RADIOMODULE_HPP */