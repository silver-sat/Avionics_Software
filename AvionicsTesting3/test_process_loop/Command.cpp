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
#include "Message.h"
#include "log_utility.h"
#include "AvionicsBoard.h"
#include "mock_power_board.h"
#include "mock_radio_board.h"
#include "mock_payload_board.h"

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
    Log.traceln("Acknowledging command");
    auto message = Message(Message::acknowledgement, "");
    extern MockRadioBoard radio;
    return radio.send_message(message);
};

/**
 * @brief Execute the command
 *
 * @return true successful
 * @return false error
 */

bool Command::execute_command()
{
    Log.traceln("Executing command");
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
    auto status = Command::acknowledge_command();
    Log.verboseln("Unknown");
    return status;
};

/**
 * @brief Execute unknown command
 *
 * @return false error
 */
bool CommandUnknown::execute_command()
{
    Command::execute_command();
    Log.errorln("Unknown");
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
    auto status = Command::acknowledge_command();
    Log.verboseln("Invalid");
    return status;
};

/**
 * @brief Execute invalid command
 *
 * @return false error
 */
bool CommandInvalid::execute_command()
{
    Command::execute_command();
    Log.errorln("Invalid");
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
    auto status = Command::acknowledge_command();
    Log.verboseln("NoOperate");
    return status;
};

/**
 * @brief Execute NoOperate command
 *
 * @return true successful
 */

bool CommandNoOperate::execute_command()
{
    Command::execute_command();
    Log.verboseln("NoOperate");
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
 * @brief Acknowledge PayComms command
 *
 */

bool CommandPayComms::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("PayComms");
    return status;
};

bool CommandPayComms::execute_command()
{

    auto status = Command::execute_command();
    Log.verboseln("PayComms");
    extern MockPayloadBoard payload;
    return payload.tweet() && status;
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
 * @brief Acknowledge ReportT command
 *
 */

bool CommandReportT::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("ReportT");
    return status;
};

bool CommandReportT::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("ReportT");
    extern AvionicsBoard avionics;
    extern MockRadioBoard radio;
    auto timestamp = avionics.get_timestamp();
    if (timestamp == "ERROR")
    {
        status = false;
    };
    auto message = Message(Message::response, timestamp);
    return radio.send_message(message) && status;
};

/**
 * @brief Construct a new Command Twee Slee:: Command Twee Slee object
 *
 */

CommandTweeSlee::CommandTweeSlee()
{
    _action = CommandTweeSlee::twee_slee;
};

/**
 * @brief Acknowledge TweeSlee command
 *
 * @return true successful
 * @return false error
 */

bool CommandTweeSlee::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("TweeSlee");
    extern MockRadioBoard radio;
    auto message = Message(Message::local_command, "STOP");
    return radio.send_message(message) && status;
};

/**
 * @brief Execute TweeSlee command
 *
 * @return true successful
 * @return false error
 */

bool CommandTweeSlee::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("TweeSlee");
    extern MockPayloadBoard payload;
    return payload.end_activity() && status;
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
 * @brief Acknowledge Watchdog command
 *
 * @return true successful
 * @return false error
 */

bool CommandWatchdog::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("Watchdog");
    return status;
};

bool CommandWatchdog::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("Watchdog");
    extern AvionicsBoard avionics;
    return avionics.watchdog_force_reset() && status;
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
    auto status = Command::acknowledge_command();
    Log.verboseln("BeaconSp: %d seconds", _seconds);
    return status;
};

/**
 * @brief Execute BeaconSp command
 *
 * @return true
 * @return false
 */

bool CommandBeaconSp::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("BeaconSp");
    extern AvionicsBoard avionics;
    return avionics.set_beacon_interval(_seconds) && status;
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
 * @brief Acknowlege PicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandPicTimes::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("PicTimes: Year: %d Month: %d Day: %d Hour: %d Minute %d Second %d",
                  _time.year, _time.month, _time.day, _time.hour, _time.minute, _time.second);
    return status;
}

/**
 * @brief Execute PicTimes command
 *
 * @return true successful
 * @return false error
 */
bool CommandPicTimes::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("PicTimes");
    extern AvionicsBoard avionics;
    DateTime time = DateTime(_time.year, _time.month, _time.day, _time.hour, _time.minute, _time.second);
    return avionics.set_picture_time(time) && status;
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
 * @return true successful
 * @return false error
 */

bool CommandSetClock::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("SetClock: Year: %d Month: %d Day: %d Hour: %d Minute %d Second %d",
                  _time.year, _time.month, _time.day, _time.hour, _time.minute, _time.second);
    return status;
}

/**
 * @brief Execute SetClock command
 *
 * @return true successful
 * @return false error
 */

bool CommandSetClock::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("SetClock");
    extern AvionicsBoard avionics;
    DateTime time = DateTime(_time.year, _time.month, _time.day, _time.hour, _time.minute, _time.second);
    return avionics.set_external_rtc(time) && status;
}

/**
 * @brief Construct a new Command Get Pic Times:: Command Get Pic Times object
 *
 */

CommandGetPicTimes::CommandGetPicTimes()
{
    _action = Command::get_pic_times;
};

/**
 * @brief Acknowledge GetPicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPicTimes::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("GetPicTimes");
    return status;
};

/**
 * @brief  Execute GetPicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPicTimes::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("GetPicTimes");
    extern AvionicsBoard avionics;
    extern MockRadioBoard radio;
    auto message = Message(Message::response, avionics.get_pic_times());
    return radio.send_message(message) && status;
};

/**
 * @brief Construct a new Command Get Telemetry:: Command Get Telemetry object
 *
 */

CommandGetTelemetry::CommandGetTelemetry()
{
    _action = Command::get_telemetry;
};

/**
 * @brief Acknowledge GetTelemetry command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetTelemetry::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("GetTelemetry");
    return status;
};

/**
 * @brief  Execute GetTelemetry command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetTelemetry::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("GetTelemetry");
    extern AvionicsBoard avionics;
    extern MockRadioBoard radio;
    auto message = Message(Message::response, avionics.get_telemetry());
    return radio.send_message(message) && status;
};
/**
 * @brief Construct a new Command Get Power:: Command Get Power object
 *
 */

CommandGetPower::CommandGetPower()
{
    _action = Command::get_power;
};

/**
 * @brief Acknowledge GetPower command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPower::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("GetPower");
    return status;
};

/**
 * @brief  Execute GetPower command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPower::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("GetPower");
    extern MockPowerBoard power;
    extern MockRadioBoard radio;
    auto message = Message(Message::response, power.get_power_detail());
    return radio.send_message(message) && status;
};
/**
 * @brief Construct a new Command Get Photos:: Command Get Photos object
 *
 */

CommandGetPhotos::CommandGetPhotos()
{
    _action = Command::get_photos;
};

/**
 * @brief Acknowledge GetPhotos command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPhotos::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("GetPhotos");
    return status;
};

/**
 * @brief  Execute GetPhotos command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPhotos::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("GetPhotos");
    extern MockPayloadBoard payload;
    extern MockRadioBoard radio;
    auto message = Message(Message::response, String(payload.get_photo_count()).c_str());
    return radio.send_message(message) && status;
};

/**
 * @brief Construct a new Command Get Comms:: Command Get Comms object
 *
 */

CommandGetComms::CommandGetComms()
{
    _action = Command::get_comms;
};

/**
 * @brief Acknowledge GetComms command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetComms::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("GetComms");
    return status;
};

/**
 * @brief  Execute GetComms command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetComms::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("GetComms");
    extern MockPayloadBoard payload;
    extern MockRadioBoard radio;
    auto message = Message(Message::local_command, "GetComms");
    return radio.send_message(message) && status;
};

/**
 * @brief Construct a new Command Get Beacon Interval:: Command Get Beacon Interval object
 *
 */

CommandGetBeaconInterval::CommandGetBeaconInterval()
{
    _action = Command::get_beacon_interval;
};

/**
 * @brief Acknowledge GetBeaconInterval command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetBeaconInterval::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("GetBeaconInterval");
    return status;
};

/**
 * @brief  Execute GetBeaconInterval command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetBeaconInterval::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("GetBeaconInterval");
    extern AvionicsBoard avionics;
    extern MockRadioBoard radio;
    auto message = Message(Message::response, String(avionics.get_beacon_interval()).c_str());
    return radio.send_message(message) && status;
};

/**
 * @brief Construct a new Command Send Test Packet:: Command Send Test Packet object
 *
 */

CommandSendTestPacket::CommandSendTestPacket()
{
    _action = Command::send_test_packet;
};

/**
 * @brief Acknowledge SendTestPacket command
 *
 * @return true successful
 * @return false error
 */

bool CommandSendTestPacket::acknowledge_command()
{
    auto status = Command::acknowledge_command();
    Log.verboseln("SendTestPacket");
    return status;
};

bool CommandSendTestPacket::execute_command()
{
    auto status = Command::execute_command();
    Log.verboseln("SendTestPacket");
    extern MockRadioBoard radio;
    auto message = Message(Message::response, "TEST");
    return radio.send_message(message) && status;
};