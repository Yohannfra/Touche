#include "Timer.hpp"

Timer::Timer(bool startDirectly)
{
    this->reset();
    if (startDirectly) {
        this->start();
    }
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
