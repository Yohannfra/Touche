#include <nrf.h>

void mac_address_get(uint8_t mac_address[6])
{
    unsigned int device_addr_0 = NRF_FICR->DEVICEADDR[0];
    unsigned int device_addr_1 = NRF_FICR->DEVICEADDR[1];

    const uint8_t* part_0 = (const uint8_t*)(&device_addr_0);
    const uint8_t* part_1 = (const uint8_t*)(&device_addr_1);

    mac_address[0] = part_1[1];
    mac_address[1] = part_1[0];
    mac_address[2] = part_0[3];
    mac_address[3] = part_0[2];
    mac_address[4] = part_0[1];
    mac_address[5] = part_0[0];
}
