/**
 * @file ExternalWatchdog.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief ExternalWatchdog for SilverSat
 * @version 1.0.1
 * @date 2022-08-01
 *
 *
 */

#ifndef EXTERNAL_WATCHDOG_H
#define EXTERNAL_WATCHDOG_H

/**
 * @brief ExternalWatchdog constants
 *
 */

constexpr unsigned long watchdog_lower_boundary{ 24 }; /**< 23.5 milliseconds */

/**
 * @brief ExternalWatchdog
 *
 */
class ExternalWatchdog {
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
  unsigned long m_last_action_time{ 0 };
  bool m_force_reset{ false };
};

#endif  // EXTERNAL_WATCHDOG_H
