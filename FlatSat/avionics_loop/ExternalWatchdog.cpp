/**
 * @file ExternalWatchdog.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat External Watchdog Timer
 * @version 1.1.0
 * @date 2022-08-01
 *
 *
 */

#include "ExternalWatchdog.h"
#include "log_utility.h"
#include "board_configuration.h"
#include <Arduino.h>

/**
 * @brief Construct a new ExternalWatchdog object
 *
 */

ExternalWatchdog::ExternalWatchdog() {
  m_last_action_time = millis();
  pinMode(WDTICK, OUTPUT);
}

/**
 * @brief Trigger the watchdog
 *
 */

void ExternalWatchdog::trigger() {
  if (!m_force_reset && (millis() - m_last_action_time > watchdog_lower_boundary)) {
    digitalWrite(WDTICK, HIGH);
    digitalWrite(WDTICK, LOW);
    m_last_action_time = millis();
  };
};

/**
 * @brief Set force reset
 *
 */

void ExternalWatchdog::set_force_reset() {
  m_force_reset = true;
};
