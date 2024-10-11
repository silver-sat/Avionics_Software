/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat External Watchdog Timer
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

  void service();

  /**
   * @brief Set force reset
   *
   */

  void force_reset();

private:
  unsigned long m_last_action_time{0};
};