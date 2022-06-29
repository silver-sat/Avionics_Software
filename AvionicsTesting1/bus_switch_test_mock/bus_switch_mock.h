//
// Mock Bus Switch for demonstration and testing
// Lee A. Congdon
// 29 June 2022
//

#ifndef BUS_SWITCH_MOCK_H
#define BUS_SWITCH_MOCK_H

#define OE_PIN "??"
#define OE_OVERBAR "??"

#define BUFFER_SIZE 16

#include <CircularBuffer.h>

enum Action {
    CREATE,
    DISABLE,
    ENABLE
};

// Define log entry structure

struct LogEntry {
    uint32_t time_stamp;
    Action action;
}; 

// Define bus switch object

class BusSwitch {
public:
    BusSwitch();
    bool enable();
    bool disable();
    const String _oe_pin = OE_PIN;
    const String _oe_overbar_pin = OE_OVERBAR;
    CircularBuffer<LogEntry, BUFFER_SIZE> _debug_log;
};

#endif