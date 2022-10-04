/**
 * @file Watchdog.cpp
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
    m_last_action_time = millis();
    pinMode(WDTICK, OUTPUT);
    pinMode(RESET, INPUT);
}

/**
 * @brief Trigger the watchdog
 *
 * @return true successful
 * @return false error
 */

bool Watchdog::trigger()
{
    auto reset = digitalRead(RESET);
    if (reset != m_reset_pin_state)
    {
        if (!reset)
        {
            Log.fatalln("Reset pin changed state to %d ", reset);
            if (m_force_reset)
            {
                m_force_reset = false;
            };
        }
        else
        {
            Log.infoln("Reset pin changed state to %d ", reset);
        };
        m_reset_pin_state = reset;
    };

    if (!m_force_reset && (millis() - m_last_action_time > watchdog_lower_boundary))
    {
        digitalWrite(WDTICK, HIGH);
        digitalWrite(WDTICK, LOW);
        m_last_action_time = millis();
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
    m_force_reset = true;
    return true;
};
