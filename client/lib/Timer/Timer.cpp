/**
 * @file Timer.cpp
 * @brief timer class
 * @author Assouline Yohann
 * @date 2020-12-24
 */

#include "Timer.hpp"

Timer::Timer()
{
    this->reset();
}

void Timer::start()
{
    _time = millis();
}

void Timer::reset()
{
    _time = 0;
}

unsigned long Timer::getTimeElapsed()
{
    return millis() - _time;
}

bool Timer::isRunning()
{
    return _time != 0;
}
