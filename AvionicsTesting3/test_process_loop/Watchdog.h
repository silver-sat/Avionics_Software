/**
 * @file Watchdog.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Watchdog for SilverSat
 * @version 1.0.0
 * @date 2022-08-01
 *
 *
 */

#ifndef TEST_WATCHDOG_H
#define TEST_WATCHDOG_H

#include "board_configuration.h"

#define WATCHDOG_LOWER_BOUNDARY 24   // 23.5 milliseconds
#define WATCHDOG_UPPER_BOUNDARY 2000 // 2 seconds

/**
 * @brief Watchdog
 *
 */
class Watchdog
{
public:
  /**
   * @brief Construct a new Watchdog object
   *
   */

  Watchdog();

  /**
   * @brief Trigger the watchdog
   *
   * @return true successful
   * @return false error
   */

  bool trigger();

  /**
   * @brief Set force reset
   *
   * @return true successful
   * @return false error
   */
  bool set_force_reset();

private:
  unsigned long _last_action_time{0};
  bool _force_reset{false};
  int _reset_pin_state{};
};

#endif // TEST_WATCHDOG_H
