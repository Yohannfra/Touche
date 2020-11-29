#include "RadioModule.hpp"

NRF24 nrf24;

RadioModule::RadioModule()
{

}

void RadioModule::init()
{
    #if 0
    while (1) {
        if (!nrf24.init())
            Serial.println("NRF24 init failed");
        else {
            Serial.println("NRF24 init ok");
            break;
        }
        delay(500);
    }


    if (!nrf24.setChannel(1))
        Serial.println("setChannel failed");
    else
        Serial.println("setChannel ok");

    if (!nrf24.setThisAddress((uint8_t*)"serv1", 5))
        Serial.println("setThisAddress failed");
    else
        Serial.println("setThisAddress ok");

    if (!nrf24.setPayloadSize(sizeof(unsigned long)))
        Serial.println("setPayloadSize failed");
    else
        Serial.println("setPayloadSize ok");

    if (!nrf24.setRF(NRF24::NRF24DataRate1Mbps, NRF24::NRF24TransmitPower0dBm))
        Serial.println("setRF failed");
    else
        Serial.println("setRF ok");

    Serial.println("NRF24 initialised");
#endif

delay(500);
 if (!nrf24.init())
    Serial.println("NRF24 init failed");
  // Defaults after init are 2.402 GHz (channel 2)
  // Now be compatible with Mirf ping_client
 if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setThisAddress((uint8_t*)"serv1", 5))
    Serial.println("setThisAddress failed");
  if (!nrf24.setPayloadSize(sizeof(unsigned long)))
    Serial.println("setPayloadSize failed");
  if (!nrf24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm))
    Serial.println("setRF failed");
  Serial.println("initialised");

}

void RadioModule::wait_for_message()
{
    nrf24.waitAvailable();

    unsigned long data;
    uint8_t len = sizeof(data);

    if (!nrf24.recv((uint8_t*)&data, &len)) {
        Serial.println("read failed");
    } else {
        Serial.print("Recvd: ");
        Serial.println(data);
    }

#if 0

    if (nrf24.available()) {
        Serial.println("Something is available");

        unsigned long data;
        uint8_t len = sizeof(data);
        if (!nrf24.recv((uint8_t*)&data, &len))
            Serial.println("read failed");

        Serial.print("Recvd: ");
        Serial.println(data);


    } else {
        Serial.println("Nothing");
    }
    #endif
}


/*
    see https://platformio.org/lib/show/42/nRF24
*/
