//
// Mock bus switch for demonstration and testing
// Lee A. Congdon
// 29 June 2022
//

#include "bus_switch_mock.h"

// Constructor

BusSwitch::BusSwitch() {
    LogEntry log_entry {millis(), Action::create};
    _debug_log.push(log_entry);
};

// Disable bus

bool BusSwitch::disableBus() {
    LogEntry log_entry {millis(), Action::disable};
    _debug_log.push(log_entry);
    return true;
};

// Enable bus

bool BusSwitch::enableBus() {
    LogEntry log_entry {millis(), Action::enable};
    _debug_log.push(log_entry);
    return true;
};

// Get log size

size_t BusSwitch::getLogSize() {
    return _debug_log.size();
}

// Get log entry

BusSwitch::LogEntry BusSwitch::getLogEntry() {
    return _debug_log.shift();
}