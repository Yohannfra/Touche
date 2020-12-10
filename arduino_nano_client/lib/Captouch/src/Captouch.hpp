#ifndef CAPTOUCH_HPP
#define CAPTOUCH_HPP

#include <CapacitiveSensor.h>

#define MAX_CALIBRATIONS_SAMPLES 200

#define CAPTOUCH_ERROR_MARGIN 2000

class Captouch
{
private:
    uint8_t pin_out;
    CapacitiveSensor capacitive_sensor;
    uint8_t pin_in;

    long _calibrationSum;
    long _calibrationIndex;
    long _threshold;

public:
    Captouch(uint8_t pin_out, uint8_t pin_in);
    bool trigger_ground();
    long get_value();
    bool calibrate();
    void end_calibration(bool success);
};

#endif /* CAPTOUCH_HPP */