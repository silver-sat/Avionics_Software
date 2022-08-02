/**
 * @file test_watchdog_hardware.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Watchdog for SilverSat
 * @version 1.0.0
 * @date 2022-08-01
 *
 *
 */

#include "Watchdog.h"
#include "log_utility.h"
#include <Arduino.h>

/**
 * @brief Construct a new Watchdog object
 *
 */

Watchdog::Watchdog()
{
    _last_action_time = micros();
    pinMode(WDTICK_PIN, OUTPUT);
    pinMode(WDRESET_PIN, INPUT);
}

/**
 * @brief Trigger the watchdog
 *
 * @return true successful
 * @return false error
 */

bool Watchdog::trigger()
{
    auto reset = digitalRead(WDRESET_PIN);
    if (reset != _reset_pin_state)
    {
        if (!reset)
        {
            Log.fatalln("Reset pin changed state to %d ", reset);
            if (_force_reset)
            {
                _force_reset = false;
            };
        }
        else
        {
            Log.infoln("Reset pin changed state to %d ", reset);
        };
        _reset_pin_state = reset;
    };

    if (!_force_reset && (micros() - _last_action_time > WATCHDOG_LOWER_BOUNDARY))
    {
        digitalWrite(WDTICK_PIN, HIGH);
        digitalWrite(WDTICK_PIN, LOW);
        _last_action_time = micros();
    };
    return true;
};

/**
 * @brief Set force reset
 *
 * @return true successful
 * @return false error
 */

bool Watchdog::set_force_reset()
{
    _force_reset = true;
    return true;
};
