//
// Mock Bus Switch for demonstration and testing
// Lee A. Congdon
// 29 June 2022
//

#include "bus_switch_mock.h"

// Constructor

BusSwitch::BusSwitch() {
    LogEntry log_entry {millis(), CREATE};
    _debug_log.push(log_entry);
};

// Disable bus

bool BusSwitch::disable() {
    LogEntry log_entry {millis(), DISABLE};
    _debug_log.push(log_entry);
    return true;
};

// Enable bus

bool BusSwitch::enable() {
    LogEntry log_entry {millis(), ENABLE};
    _debug_log.push(log_entry);
    return true;
};