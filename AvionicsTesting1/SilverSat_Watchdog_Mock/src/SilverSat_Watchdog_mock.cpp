/**
 * @file SilverSat_Watchdog_mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Watchdog for demonstration and testing
 * @version 1.0.0
 * @date 2022-06-30
 *
 *
 */

#include <SilverSat_Watchdog_mock.h>

// Create the watchdog object

Watchdog::Watchdog()
{
    _last_action_time = millis();
    _lower_boundary_active = false;
    LogEntry log_entry{_last_action_time, Event::create_watchdog};
    _debug_log.push(log_entry);
}

// Reset the watchdog

void Watchdog::reset()
{
    uint32_t time_stamp = millis();
    if ((time_stamp - _last_action_time) <= WATCHDOG_UPPER_BOUNDARY)
    {

        LogEntry log_entry{time_stamp, Event::reset_watchdog};
        _debug_log.push(log_entry);
    }
    else
    {

        LogEntry log_entry{time_stamp, Event::late_reset_watchdog};
        _debug_log.push(log_entry);
    }
    _last_action_time = time_stamp;
    _lower_boundary_active = false;
}

// Trigger the WDI pin

void Watchdog::trigger()
{
    uint32_t time_stamp = millis();
    uint32_t interval = time_stamp - _last_action_time;

    if (interval < WATCHDOG_LOWER_BOUNDARY && _lower_boundary_active)
    {

        LogEntry log_entry{time_stamp, Event::early_trigger_watchdog};
        _debug_log.push(log_entry);

        Watchdog::reset();
    }
    else if (interval > WATCHDOG_UPPER_BOUNDARY)
    {

        LogEntry log_entry{time_stamp, Event::late_trigger_watchdog};
        _debug_log.push(log_entry);

        Watchdog::reset();
    }
    else
    {

        LogEntry log_entry{time_stamp, Event::trigger_watchdog};
        _debug_log.push(log_entry);
        _last_action_time = time_stamp;
        _lower_boundary_active = true;
    };
};

// Dump debug log

void Watchdog::dumpLog()
{
    auto count = _debug_log.size();
    Serial.print("There are ");
    Serial.print(count);
    Serial.println(" entries in the log");
    for (auto index = count; index > 0; index--)
    {
        auto log_entry = _debug_log.shift();
        Serial.print("Entry: ");
        switch (log_entry.event)
        {
        case Watchdog::Event::create_watchdog:
            Serial.print("Watchdog created at ");
            break;
        case Watchdog::Event::reset_watchdog:
            Serial.print("Watchdog reset at ");
            break;
        case Watchdog::Event::late_reset_watchdog:
            Serial.print("Watchdog reset late at ");
            break;
        case Watchdog::Event::early_trigger_watchdog:
            Serial.print("Watchdog triggered early at ");
            break;
        case Watchdog::Event::trigger_watchdog:
            Serial.print("Watchdog triggered at ");
            break;
        case Watchdog::Event::late_trigger_watchdog:
            Serial.print("Watchdog triggered late at ");
            break;
        }
        Serial.println(log_entry.time_stamp);
    };
};