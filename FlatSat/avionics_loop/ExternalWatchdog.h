/**
 * @file ExternalWatchdog.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat External Watchdog Timer
 * @version 1.0.1
 * @date 2022-08-01
 *
 * This file declares the class that interfaces with the external watchdog
 *
 */

#pragma once

/**
 * @brief ExternalWatchdog constants
 *
 */

constexpr unsigned long watchdog_lower_boundary{24}; /**< 23.5 milliseconds */

/**
 * @brief ExternalWatchdog
 *
 */

class ExternalWatchdog final
{
public:
  /**
   * @brief Construct a new ExternalWatchdog object
   *
   */

  ExternalWatchdog();

  /**
   * @brief Trigger the watchdog
   *
   */

  void trigger();

  /**
   * @brief Set force reset
   *
   */

  void set_force_reset();

private:
  unsigned long m_last_action_time{0};
  bool m_force_reset{false};
};