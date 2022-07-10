/**
 * @file SilverSat_Bus_Switch_mock.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Header for mock bus switch for testing and demonstration
 * @version 1.0.1
 * @date 2022-06-29
 *
 */

#ifndef SILVERSAT_BUS_SWITCH_MOCK_H
#define SILVERSAT_BUS_SWITCH_MOCK_H

#define OE_PIN "??"
#define OE_OVERBAR "??"

#define BUFFER_SIZE 16

#include <Arduino.h>
#include <CircularBuffer.h>

/**
 * @brief The bus switch object
 *
 */
class BusSwitch
{
public:
    BusSwitch();

    /**
     * @brief Available actions
     *
     */
    enum Action
    {
        create,
        disable,
        enable,
    };

    /**
     * @brief Log entry structure
     *
     */
    struct LogEntry
    {
        uint32_t time_stamp;
        Action action;
    };

    /**
     * @brief Enable the bus
     *
     * @return true if successful
     * @return false otherwise
     */

    bool enableBus();

    /**
     * @brief Disable the bus
     *
     * @return true if successful
     * @return false otherwise
     */

    bool disableBus();

    /**
     * @brief Get the log size
     *
     * @return size_t log size
     */

    size_t getLogSize();

    /**
     * @brief Get the next log entry
     *
     * @return LogEntry
     */

    LogEntry getLogEntry();

private:
    const String _oe_pin = OE_PIN;
    const String _oe_overbar_pin = OE_OVERBAR;
    CircularBuffer<LogEntry, BUFFER_SIZE> _debug_log;
};

#endif