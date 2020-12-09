#ifndef TIMER_HPP
#define TIMER_HPP

#include <Arduino.h>

class Timer
{
private:
    unsigned long _time;
public:
    Timer();
    void start();
    void reset();
    unsigned long getTimeElapsed();
    bool isRunning();
};

#endif /* TIMER_HPP */