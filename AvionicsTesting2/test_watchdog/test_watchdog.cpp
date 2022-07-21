/**
 * @file test_watchdog.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test watchdog
 * @version 1.0.0
 * @date 2022-07-21
 *
 *
 */

#include "test_watchdog.h"

// Create the watchdog object

Watchdog::Watchdog()
{
    _last_action_time = micros();
    _lower_boundary_active = false;
    pinMode(WDTICK_PIN, OUTPUT);
    pinMode(WDRESET_PIN, INPUT);
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

    if (interval < WATCHDOG_LOWER_BOUNDARY && _lower_boundary_active)
    {

        LogEntry log_entry{time_stamp, Event::early_trigger_watchdog};
        _debug_log.push(log_entry);
    }
    else if (interval > WATCHDOG_UPPER_BOUNDARY)
    {

        LogEntry log_entry{time_stamp, Event::late_trigger_watchdog};
        _debug_log.push(log_entry);
    }
    else
    {
        LogEntry log_entry{time_stamp, Event::trigger_watchdog};
        _debug_log.push(log_entry);
        _last_action_time = time_stamp;
        _lower_boundary_active = true;
    };
};

void Watchdog::check_reset()
{
    unsigned long time_stamp = micros();
    if (digitalRead(WDRESET_PIN) == HIGH)
    {

        LogEntry log_entry{time_stamp, Event::received_reset};
        _debug_log.push(log_entry);
    }
    else
    {
        LogEntry log_entry{time_stamp, Event::no_reset_received};
        _debug_log.push(log_entry);
    }
}

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
        case Watchdog::Event::early_trigger_watchdog:
            Serial.print("Watchdog triggered early at ");
            break;
        case Watchdog::Event::trigger_watchdog:
            Serial.print("Watchdog triggered at ");
            break;
        case Watchdog::Event::late_trigger_watchdog:
            Serial.print("Watchdog triggered late at ");
            break;
        case Watchdog::Event::no_reset_received:
            Serial.print("Watchdog had not issued reset at ");
            break;
        case Watchdog::Event::received_reset:
            Serial.print("Watchdog issued reset at ");
            break;

        default:
            Serial.print("Undefined log entry at ");
        }
        Serial.println(log_entry.time_stamp);
    };
};