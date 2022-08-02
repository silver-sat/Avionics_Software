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

// #define WDTICK_PIN PIN_PB23
#define WDTICK_PIN 2  // for testing
#define WDRESET_PIN 3 // for testing

#define WATCHDOG_LOWER_BOUNDARY 23500   // 23.5 milliseconds
#define WATCHDOG_UPPER_BOUNDARY 2000000 // 2 seconds

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
  const int _wdi_pin = WDTICK_PIN;
  const int _wdreset_pin = WDRESET_PIN;
  unsigned long _last_action_time{0};
  bool _force_reset{false};
  int _reset_pin_state{};
};

#endif
