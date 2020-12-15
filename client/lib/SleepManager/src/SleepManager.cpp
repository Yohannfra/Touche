#include "DebugLog.hpp"
#include "SleepManager.hpp"
#include <avr/sleep.h>

#define BUTTON_PIN (3)

SleepManager::SleepManager()
{
}

void wakeup()
{
    sleep_disable();
    detachInterrupt(digitalPinToInterrupt(BUTTON_PIN));
    DEBUG_LOG_LN("Waking up");
}

void SleepManager::sleep()
{
    sleep_enable();
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), wakeup, LOW); // attaching a interrupt to pin d2
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Setting the sleep mode, in our case full sleep
    DEBUG_LOG_LN("Going to sleep...");
    delay(500);
    DEBUG_LOG_LN("BYE");
    Serial.flush();
    sleep_cpu();
}
