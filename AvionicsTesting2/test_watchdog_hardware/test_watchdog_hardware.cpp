/**
 * @file test_watchdog_hardware.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test watchdog hardware
 * @version 1.0.0
 * @date 2022-07-22
 *
 *
 */

#include "test_watchdog_hardware.h"

// Create the watchdog object

Watchdog::Watchdog()
{
    _last_action_time = micros();
    pinMode(WDTICK_PIN, OUTPUT);
    LogEntry log_entry{_last_action_time, Event::create_watchdog};
    _debug_log.push(log_entry);
}

// Trigger the WDI pin

void Watchdog::trigger()
{
    digitalWrite(WDTICK_PIN, HIGH);
    digitalWrite(WDTICK_PIN, LOW);

    unsigned long time_stamp = micros();
    unsigned long interval = time_stamp - _last_action_time;

    if (interval < WATCHDOG_LOWER_BOUNDARY)
    {

        LogEntry log_entry{time_stamp, Event::trigger_watchdog_before_window};
        _debug_log.push(log_entry);
    }
    else if (interval > WATCHDOG_UPPER_BOUNDARY)
    {

        LogEntry log_entry{time_stamp, Event::trigger_watchdog_after_window};
        _debug_log.push(log_entry);
    }
    else
    {
        LogEntry log_entry{time_stamp, Event::trigger_watchdog_in_window};
        _debug_log.push(log_entry);
    };
        _last_action_time = time_stamp;
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
        case Watchdog::Event::trigger_watchdog_before_window:
            Serial.print("Watchdog triggered before window at ");
            break;
        case Watchdog::Event::trigger_watchdog_in_window:
            Serial.print("Watchdog triggered in window at ");
            break;
        case Watchdog::Event::trigger_watchdog_after_window:
            Serial.print("Watchdog triggered after window at ");
            break;
        case Watchdog::Event::no_reset_received:
            Serial.print("Watchdog had not issued reset at ");
            break;
        case Watchdog::Event::reset_received:
            Serial.print("Watchdog had issued reset at ");
            break;

        default:
            Serial.print("Undefined log entry at ");
        }
        Serial.println(log_entry.time_stamp);
    };
};