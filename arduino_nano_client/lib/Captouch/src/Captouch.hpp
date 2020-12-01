#ifndef CAPTOUCH_HPP
#define CAPTOUCH_HPP

#include <CapacitiveSensor.h>

class Captouch
{
private:
    uint8_t pin_out;
    CapacitiveSensor capacitive_sensor;
    uint8_t pin_in;
    long get_value();

public:
    Captouch(uint8_t pin_out, uint8_t pin_in);
    bool trigger_ground();
    void calibrate();
};



#endif /* CAPTOUCH_HPP */