/**
 * @file SilverSat_Watchdog_mock.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Watchdog for demonstration and testing
 * @version 1.0.0
 * @date 2022-06-30
 *
 *
 */

#ifndef SILVERSAT_WATCHDOG_MOCK_H
#define SILVERSAT_WATCHDOG_MOCK_H

#define WATCHDOG_WDI_PIN "??"
#define WATCHDOG_LOWER_BOUNDARY 10
#define WATCHDOG_UPPER_BOUNDARY 300

#define BUFFER_SIZE 16

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
   * @brief Enumerate the possible actions on the object
   *
   */

  enum Event
  {
    create_watchdog,
    reset_watchdog,
    late_reset_watchdog,
    early_trigger_watchdog,
    trigger_watchdog,
    late_trigger_watchdog,
  };

  /**
   * @brief Log entry structure
   *
   *
   */

  struct LogEntry
  {
    uint32_t time_stamp;
    Event event;
  };

  /**
   * @brief Reset the watchdog
   *
   */

  void reset();

  /**
   * @brief Trigger the watchdog (notify still alive)
   *
   */

  void trigger();

  /**
   * @brief Dump the watchdog log
   *
   */

  void dumpLog();

private:
  const String _wdi_pin = WATCHDOG_WDI_PIN;
  uint32_t _last_action_time;
  bool _lower_boundary_active;
  CircularBuffer<LogEntry, BUFFER_SIZE> _debug_log;
};

#endif
