/**
 * @file SilverSat_Bus_Switch_mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Implementation of mock bus switch for testing and demonstration
 * @version 1.0.1
 * @date 2022-06-29
 *
 */

#include <SilverSat_Bus_Switch_mock.h>

// Construct a new Bus Switch:: Bus Switch object

BusSwitch::BusSwitch()
{
    LogEntry log_entry{millis(), Action::create};
    _debug_log.push(log_entry);
};

// Disable the bus

bool BusSwitch::disableBus()
{
    LogEntry log_entry{millis(), Action::disable};
    _debug_log.push(log_entry);
    return true;
};

// Enable the bus

bool BusSwitch::enableBus()
{
    LogEntry log_entry{millis(), Action::enable};
    _debug_log.push(log_entry);
    return true;
};

// Get size of the debug log

size_t BusSwitch::getLogSize()
{
    return _debug_log.size();
}

// Get a log entry and remove it from the log

BusSwitch::LogEntry BusSwitch::getLogEntry()
{
    return _debug_log.shift();
}