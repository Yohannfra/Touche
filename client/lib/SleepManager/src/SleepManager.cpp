#include "DebugLog.hpp"
#include "SleepManager.hpp"
#include <avr/sleep.h>
#include "../../../include/client_config.h"

/**
 * @brief Wakeup callback
 */
static void wakeup()
{
    sleep_disable();
    detachInterrupt(digitalPinToInterrupt(EPEE_BUTTON_PIN));
    DEBUG_LOG_LN("Waking up");
}

void SleepManager::sleep()
{
    sleep_enable();
    attachInterrupt(digitalPinToInterrupt(EPEE_BUTTON_PIN), wakeup, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    DEBUG_LOG_LN("Going to sleep...");
    delay(500);
    DEBUG_LOG_LN("BYE");
    Serial.flush();
    sleep_cpu();
}
