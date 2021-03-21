#include "VirtualGround.hpp"
#include <CapacitiveSensor.h>
#include "DebugLog.h"

#define MAX_CALIBRATIONS_SAMPLES 200 // adjust me

#define CAPTOUCH_ERROR_MARGIN 2000 // adjust me

VirtualGround::VirtualGround(uint8_t pin_out, uint8_t pin_in) : _capacitive_sensor(pin_out, pin_in)
{
    this->_pin_out = pin_out;
    this->_pin_in = pin_in;
    this->_capacitive_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate
    _calibrationSum = 0;
    _calibrationIndex = 0;
    _threshold = 0;
}

long VirtualGround::get_value()
{
    long touchval = this->_capacitive_sensor.capacitiveSensorRaw(40); // adjust the value
    return touchval;
}

bool VirtualGround::trigger_ground()
{
    if (_threshold == 0)
        return false;

    long val = this->get_value();
    DEBUG_LOG_VAL("VirtualGround value: ", val);
    if (_threshold - CAPTOUCH_ERROR_MARGIN < val && val < _threshold + CAPTOUCH_ERROR_MARGIN)
        return true;
    return false;
}

bool VirtualGround::calibrate()
{
    _calibrationSum += this->get_value();
    _calibrationIndex += 1;

    return _calibrationIndex == MAX_CALIBRATIONS_SAMPLES - 1;
}

void VirtualGround::end_calibration(bool success)
{
    if (success && _calibrationIndex > 0 /* to avoid div by 0 */) {
        _threshold = _calibrationSum / _calibrationIndex;
        DEBUG_LOG_VAL("Treshold is now: ", _threshold);
    }
    _calibrationIndex = 0;
    _calibrationSum = 0;
}
