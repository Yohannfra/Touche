/*
Touché Project
Copyright (C) 2021 Assouline Yohann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "VirtualGround.hpp"

#include "DebugLog.h"

#include <CapacitiveSensor.h>

#define MAX_CALIBRATIONS_SAMPLES 100

VirtualGround::VirtualGround(uint8_t pin_out, uint8_t pin_in) : _capacitive_sensor(pin_out, pin_in)
{
    this->_pin_out = pin_out;
    this->_pin_in = pin_in;
    this->_capacitive_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);  // turn off autocalibrate
    this->_capacitive_sensor.set_CS_Timeout_Millis(2500);
    _calibrationSum = 0;
    _calibrationIndex = 0;
    _threshold = 0;
    _tolerance = 0;
    _pisteEnabled = false;
}

long VirtualGround::get_value()
{
    // 5 is a good compromise to have both speed and precision
    return this->_capacitive_sensor.capacitiveSensorRaw(5);
}

bool VirtualGround::trigger_ground()
{
    if (_threshold == 0)
        return false;

    const uint8_t NB_OF_TIME_TO_SAMPLE = 5;
    long sum = 0;

    for (uint8_t i = 0; i < NB_OF_TIME_TO_SAMPLE; i++) {
        long val = this->get_value();
        DEBUG_LOG_VAL("trigger_ground value: ", val);
        sum += val;
    }
    sum = sum / NB_OF_TIME_TO_SAMPLE;

    DEBUG_LOG_VAL("trigger_ground final: ", sum);

    if (_pisteEnabled && sum > _threshold) {  // hit the piste
        return true;
    }

    if (_threshold - _tolerance <= sum && sum <= _threshold + _tolerance) {
        return true;
    }
    return false;
}

bool VirtualGround::calibrate()
{
    long val = this->get_value();
    DEBUG_LOG_VAL("calibration val: ", val);

    if (val < 0) {  // an error occured, -2 can occure sometimes
        goto ret;
    }

    _calibrationSum += val;
    _calibrationIndex += 1;

ret:
    return _calibrationIndex == MAX_CALIBRATIONS_SAMPLES;
}

void VirtualGround::end_calibration(bool success)
{
    if (success && _calibrationIndex > 0 /* to avoid div by 0 */) {
        _threshold = _calibrationSum / _calibrationIndex;
        _tolerance = (float)_threshold / 6.66f;  //  ~ 15% of the _treshold
        DEBUG_LOG_VAL("Treshold is now: ", _threshold);
        DEBUG_LOG_VAL("Tolerance is now: ", _tolerance);
    }
    _calibrationIndex = 0;
    _calibrationSum = 0;
}

void VirtualGround::setPisteEnabled(bool state)
{
    _pisteEnabled = state;
}
