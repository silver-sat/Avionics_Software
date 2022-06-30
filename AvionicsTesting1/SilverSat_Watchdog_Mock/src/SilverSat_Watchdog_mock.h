//
// Mock Watchdog for demonstration and testing
// Lee A. Congdon
// 30 June 2022
//

#ifndef SILVERSAT_WATCHDOG_MOCK_H
#define SILVERSAT_WATCHDOG_MOCK_H

#define WATCHDOG_WDI_PIN "??"
#define WATCHDOG_LOWER_BOUNDARY 10
#define WATCHDOG_UPPER_BOUNDARY 300

#define BUFFER_SIZE 16

#include <Arduino.h>
#include <CircularBuffer.h>

class Watchdog
{
public:
  Watchdog();

  // Events

  enum Event
  {
    create_watchdog,
    reset_watchdog,
    late_reset_watchdog,
    early_trigger_watchdog,
    trigger_watchdog,
    late_trigger_watchdog,
  };

  // Log entry structure

  struct LogEntry
  {
    uint32_t time_stamp;
    Event event;
  };

  //  Member functions

  void reset();
  void trigger();
  void dumpLog();

  // Member variables

private:
  const String _wdi_pin = WATCHDOG_WDI_PIN;
  uint32_t _last_action_time;
  bool _lower_boundary_active;
  CircularBuffer<LogEntry, BUFFER_SIZE> _debug_log;
};

#endif
