/**
 * @file Command.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 * @version 1.0.1
 * @date 2022-07-25
 *
 *
 */

#include "Command.h"
#include "timestamp.h"
#include "AvionicsBoard.h"

/**
 * @brief Construct a new Command object
 *
 */

Command::Command(){

};

/**
 * @brief get the command operation
 *
 * @return Command::operation
 */
Command::operation Command::get_operation()
{
    return _action;
};

/**
 * @brief Acknowledge the command
 *
 */

bool Command::acknowledge_command()
{
    timestamp();
    Serial.println("Acknowledging command");
    return true;
};

/**
 * @brief Execute the command
 *
 * @return true successful
 * @return false error
 */

bool Command::execute_command()
{
    timestamp();
    Serial.print("Executing command");
    return true;
};

/**
 * @brief Construct a new Command Unknown:: Command Unknown object
 *
 */

CommandUnknown::CommandUnknown()
{
    _action = Command::unknown;
};

/**
 * @brief Acknowledge unknown command
 *
 * @return true successful
 * @return false error
 */

bool CommandUnknown::acknowledge_command()
{
    Serial.println(" Unknown");
    return Command::acknowledge_command();
};

/**
 * @brief Execute unknown command
 *
 * @return false error
 */
bool CommandUnknown::execute_command()
{
    Command::execute_command();
    Serial.println(" Unknown");
    return false;
}

/**
 * @brief Construct a new Command Invalid:: Command Invalid object
 *
 */

CommandInvalid::CommandInvalid()
{
    _action = Command::invalid;
};

/**
 * @brief Acknowledge invalid command
 *
 * @return true successful
 * @return false error
 */

bool CommandInvalid::acknowledge_command()
{
    Serial.println(" Invalid");
    return Command::acknowledge_command();
};

/**
 * @brief Execute invalid command
 *
 * @return false error
 */
bool CommandInvalid::execute_command()
{
    Command::execute_command();
    Serial.println(" Invalid");
    return false;
};

/**
 * @brief Construct a new Command No Operate:: Command No Operate object
 *
 */

CommandNoOperate::CommandNoOperate()
{
    _action = Command::no_operate;
};

/**
 * @brief Acknowledge NoOperate command
 *
 * @return true successful
 * @return false error
 */

bool CommandNoOperate::acknowledge_command()
{
    Serial.println(" NoOperate");
    return Command::acknowledge_command();
};

/**
 * @brief Execute NoOperate command
 *
 * @return true successful
 */

bool CommandNoOperate::execute_command()
{
    Command::execute_command();
    Serial.println(" NoOperate");
    return true;
};

/**
 * @brief Construct a new Command Pay Comms:: Command Pay Comms object
 *
 */

CommandPayComms::CommandPayComms()
{
    _action = Command::pay_comms;
};

/**
 * @brief Construct a new Command Report T:: Command Report T object
 *
 */

CommandReportT::CommandReportT()
{
    _action = Command::report_t;
};

/**
 * @brief Construct a new Command Twee Slee:: Command Twee Slee object
 *
 */

CommandTweeSlee::CommandTweeSlee()
{
    _action = Command::twee_slee;
};

/**
 * @brief Construct a new Command Watchdog:: Command Watchdog object
 *
 */

CommandWatchdog::CommandWatchdog()
{
    _action = Command::watchdog;
};

/**
 * @brief Construct a new Command Beacon Sp:: Command Beacon Sp object
 *
 * @param seconds interval between beacons
 */

CommandBeaconSp::CommandBeaconSp(int seconds)
{
    _action = Command::beacon_sp;
    _seconds = seconds;
};

/**
 * @brief Acknowledge BeaconSp command
 *
 * @return true
 * @return false
 */

bool CommandBeaconSp::acknowledge_command()
{
    Serial.print("BeaconSp: ");
    Serial.print(_seconds);
    Serial.println(" seconds");
    Command::acknowledge_command();
    return true;
};

/**
 * @brief Execute BeaconSp command
 *
 * @return true
 * @return false
 */

bool CommandBeaconSp::execute_command()
{
    extern AvionicsBoard avionics;
    avionics.set_beacon_interval(_seconds);
    Command::execute_command();
    Serial.println(" BeaconSp");
    return true;
};

/**
 * @brief Construct a new Command Pic Times:: Command Pic Times object
 *
 * @param time time value
 */

CommandPicTimes::CommandPicTimes(time_value time)
{
    _action = Command::pic_times;
    _time = time;
};

/**
 * @brief Construct a new Command Set Clock:: Command Set Clock object
 *
 * @param time time value
 */

CommandSetClock::CommandSetClock(time_value time)
{
    _action = Command::set_clock;
    _time = time;
};

/**
 * @brief Acknowlege SetClock command
 *
 * @return true
 * @return false
 */

bool CommandSetClock::acknowledge_command()
{
    Serial.print("SetClock: ");
    Serial.print("Year: ");
    Serial.print(_time.year);
    Serial.print(" Month: ");
    Serial.print(_time.month);
    Serial.print(" Day: ");
    Serial.print(_time.day);
    Serial.print(" Hour: ");
    Serial.print(_time.hour);
    Serial.print(" Minute: ");
    Serial.print(_time.minute);
    Serial.print(" Second: ");
    Serial.println(_time.second);
    Command::acknowledge_command();
    return true;
}

/**
 * @brief Execute SetClock command
 *
 * @return true
 * @return false
 */

bool CommandSetClock::execute_command()
{
    // Adjust UTC offset (in hours) according to time zone, noting daylight savings time
    const auto utc_offset{4};
    extern AvionicsBoard avionics;
    DateTime utc_time = DateTime(_time.year, _time.month, _time.day, _time.hour, _time.minute, _time.second) + TimeSpan(0, 4, 0, 0);
    avionics.set_external_rtc(utc_time);
    Command::execute_command();
    Serial.println(" SetClock");
    return true;
}
