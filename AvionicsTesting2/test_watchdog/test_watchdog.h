/**
 * @file test_watchdog.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test watchdog
 * @version 1.0.0
 * @date 2022-07-21
 *
 *
 */

#ifndef TEST_WATCHDOG_H
#define TEST_WATCHDOG_H

// #define WDTICK_PIN PIN_PB23
#define WDTICK_PIN 2 // for testing
#define WDRESET_PIN 3 // for testing
#define WATCHDOG_LOWER_BOUNDARY 23500 // 23.5 milliseconds
#define WATCHDOG_UPPER_BOUNDARY 2000000 // 2 seconds

#define BUFFER_SIZE 128

#include <Arduino.h>
#include <CircularBuffer.h>

/**
 * @brief Mock watchdog
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
   * @brief Enumerate the possible log events
   *
   */

  enum Event
  {
    create_watchdog,
    trigger_watchdog_before_window,
    trigger_watchdog_in_window,
    trigger_watchdog_after_window,
    no_reset_received,
    reset_received,
  };

  /**
   * @brief Log entry structure
   *
   *
   */

  struct LogEntry
  {
    unsigned long time_stamp;
    Event event;
  };

  /**
   * @brief Notify watchdog that process is still alive
   *
   */

  void trigger();

  /**
   * @brief Determine if the watchdog has asserted a reset
   *
   */

  void check_reset();

  /**
   * @brief Dump the watchdog log
   *
   */

  void dumpLog();

private:
  const int _wdi_pin = WDTICK_PIN;
  unsigned long _last_action_time;
  CircularBuffer<LogEntry, BUFFER_SIZE> _debug_log;
};

#endif
