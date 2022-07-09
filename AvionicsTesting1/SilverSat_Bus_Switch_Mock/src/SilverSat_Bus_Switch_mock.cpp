/**
 * @file SilverSat_Bus_Switch_mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Implementation of mock bus switch for testing and demonstration
 * @version 1.0.1
 * @date 2022-07-09
 * 
 */

#include <SilverSat_Bus_Switch_mock.h>

/**
 * @brief Construct a new Bus Switch:: Bus Switch object
 * 
 */
BusSwitch::BusSwitch() {
    LogEntry log_entry {millis(), Action::create};
    _debug_log.push(log_entry);
};

/**
 * @brief Disable the bus
 * 
 * @return true if successful
 * @return false otherwise
 */
bool BusSwitch::disableBus() {
    LogEntry log_entry {millis(), Action::disable};
    _debug_log.push(log_entry);
    return true;
};

/**
 * @brief Enable the bus
 * 
 * @return true if successful
 * @return false otherwise
 */
bool BusSwitch::enableBus() {
    LogEntry log_entry {millis(), Action::enable};
    _debug_log.push(log_entry);
    return true;
};

/**
 * @brief Get size of the debug log
 * 
 * @return size_t log size
 */
size_t BusSwitch::getLogSize() {
    return _debug_log.size();
}

/**
 * @brief Get a log entry and remove it from the log
 * 
 * @return BusSwitch::LogEntry the next log entry
 */
BusSwitch::LogEntry BusSwitch::getLogEntry() {
    return _debug_log.shift();
}