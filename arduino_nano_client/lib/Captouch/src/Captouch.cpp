#include "Captouch.hpp"
#include <CapacitiveSensor.h>


#define TOUCHVAL_THREESHOLD 50000 // change me

Captouch::Captouch(uint8_t pin_out, uint8_t pin_in) : capacitive_sensor(pin_out, pin_in)
{
    this->pin_out = pin_out;
    this->pin_in = pin_in;
    this->capacitive_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate
}

long Captouch::get_value()
{
    long touchval = this->capacitive_sensor.capacitiveSensorRaw(1);
    // DEBUG_LOG_LN(touchval);
    return touchval;
}

bool Captouch::trigger_ground()
{
    return this->get_value() > TOUCHVAL_THREESHOLD;
}

void Captouch::calibrate()
{
    // TODO
}