#include "Captouch.hpp"
#include <CapacitiveSensor.h>
#include "DebugLog.hpp"

Captouch::Captouch(uint8_t pin_out, uint8_t pin_in) : capacitive_sensor(pin_out, pin_in)
{
    this->pin_out = pin_out;
    this->pin_in = pin_in;
    this->capacitive_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate
    _calibrationSum = 0;
    _calibrationIndex = 0;
    _threshold = 0;
}

long Captouch::get_value()
{
    long touchval = this->capacitive_sensor.capacitiveSensorRaw(40);

    // DEBUG_LOG_LN(touchval); // Fait tout bug wtf
    return touchval;
}

bool Captouch::trigger_ground()
{
    if (_threshold == 0)
        return false;

    long val = this->get_value();
    DEBUG_LOG_VAL("Captouch value: ", val);
    if (_threshold - CAPTOUCH_ERROR_MARGIN < val && val < _threshold + CAPTOUCH_ERROR_MARGIN)
        return true;
    return false;
}

bool Captouch::calibrate()
{
    _calibrationSum += this->get_value();
    _calibrationIndex += 1;

    return _calibrationIndex == MAX_CALIBRATIONS_SAMPLES - 1;
}

void Captouch::end_calibration(bool success)
{
    if (success && _calibrationIndex > 0 /* to avoid div by 0 */) {
        _threshold = _calibrationSum / _calibrationIndex;
        DEBUG_LOG_VAL("Treshold is now: ", _threshold);
    }
    _calibrationIndex = 0;
    _calibrationSum = 0;
}