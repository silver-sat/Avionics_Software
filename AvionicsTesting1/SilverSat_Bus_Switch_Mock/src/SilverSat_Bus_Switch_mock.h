//
// Mock bus switch for demonstration and testing
// Lee A. Congdon
// 29 June 2022
//

#ifndef SILVERSAT_BUS_SWITCH_MOCK_H
#define SILVERSAT_BUS_SWITCH_MOCK_H

#define OE_PIN "??"
#define OE_OVERBAR "??"

#define BUFFER_SIZE 16

#include <Arduino.h>
#include <CircularBuffer.h>

// Define bus switch object

class BusSwitch {
public:

    BusSwitch();

// Requested actions 

    enum Action {
        create,
        disable,
        enable,
    };

// Log entry structure

    struct LogEntry {
        uint32_t time_stamp;
        Action action;
    }; 

// Member functions

    bool enableBus();
    bool disableBus();
    size_t getLogSize();
    LogEntry getLogEntry();

// Member variables

private:

    const String _oe_pin = OE_PIN;
    const String _oe_overbar_pin = OE_OVERBAR;
    CircularBuffer<LogEntry, BUFFER_SIZE> _debug_log;

};

#endif