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
#define WATCHDOG_LOWER_BOUNDARY 24 // 23.5 milliseconds
#define WATCHDOG_UPPER_BOUNDARY 2000 // 2 seconds

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
    early_trigger_watchdog,
    trigger_watchdog,
    late_trigger_watchdog,
    no_reset_received,
    received_reset,
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
   * @brief Reset the watchdog
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
  bool _lower_boundary_active;
  CircularBuffer<LogEntry, BUFFER_SIZE> _debug_log;
};

#endif
