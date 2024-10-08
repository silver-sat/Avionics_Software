/**
 * @file Commands.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 * @version 1.3.0
 * @date 2022-07-25
 *
 * This file implements the acknowledge and execute methods for all Command objects.
 * Virtual dispatch is used to select the correct methods based on command type. Each
 * derived Command calls the base class acknowledgement method for sending an
 * acknowledgement to the ground and the base execute method for logging.
 *
 */

#include "Commands.h"
#include "avionics_constants.h"
#include "Message.h"
#include "Response.h"
#include "log_utility.h"
#include "AvionicsBoard.h"
#include "PowerBoard.h"
#include "PayloadBoard.h"
#include "CommandProcessor.h"

/**
 * @brief Acknowledge the command
 *
 * @return true successful
 * @return false error
 *
 * Called by each command type to send acknowledgment to the ground
 *
 */

bool Command::acknowledge_command()
{
    Log.traceln("Acknowledging command");
    extern CommandProcessor command_processor;
    Message message{Message::acknowledgement, ACK + " " + command_processor.get_sequence()};
    return message.send();
}

/**
 * @brief Negative acknowledge the command
 *
 * @return true successful
 * @return false error
 *
 * Send negative acknowledgement to the ground
 *
 */

bool Command::negative_acknowledge_command()
{
    Log.traceln("Negative acknowledging command");
    extern CommandProcessor command_processor;
    Message message{Message::negative_acknowledgement, NACK + " " + command_processor.get_sequence()};
    return message.send();
}

/**
 * @brief Execute the command
 *
 * @return true successful
 * @return false error
 *
 * Log command execution
 *
 */

bool Command::execute_command()
{
    Log.traceln("Executing command");
    return true;
}

/**
 * @brief Acknowlege SetClock command
 *
 * @return true successful
 * @return false error
 */

bool CommandSetClock::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("SetClock: Year: %d Month: %d Day: %d Hour: %d Minute: %d Second: %d",
                  m_time.year(), m_time.month(), m_time.day(), m_time.hour(), m_time.minute(), m_time.second());
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
    auto status{Command::execute_command()};
    Log.verboseln("SetClock");
    extern AvionicsBoard avionics;
    status = avionics.set_external_rtc(m_time) && status;
    auto response{Response{status ? "SRC" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge BeaconSp command
 *
 * @return true successful
 * @return false error
 */

bool CommandBeaconSp::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("BeaconSp: %d seconds", m_seconds);
    return status;
}

/**
 * @brief Execute BeaconSp command
 *
 * @return true successful
 * @return false error
 */

bool CommandBeaconSp::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("BeaconSp");
    extern AvionicsBoard avionics;
    status = avionics.set_beacon_interval(m_seconds) && status;
    auto response{Response{status ? "SBI" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowlege PicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandPicTimes::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("PicTimes: Year: %d Month: %d Day: %d Hour: %d Minute: %d Second: %d",
                  m_time.year(), m_time.month(), m_time.day(), m_time.hour(), m_time.minute(), m_time.second());
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
    auto status{Command::execute_command()};
    Log.verboseln("PicTimes");
    extern AvionicsBoard avionics;
    status = avionics.set_picture_time(m_time) && status;
    auto response{Response{status ? "SPT" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge ClearPicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandClearPicTimes::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("ClearPicTimes");
    return status;
}

/**
 * @brief Execute ClearPicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandClearPicTimes::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("ClearPicTimes");
    extern AvionicsBoard avionics;
    status = avionics.clear_pic_times() && status;
    auto response{Response{status ? "CPT" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge UnsetClock command
 *
 * @return true successful
 * @return false error
 */

bool CommandUnsetClock::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("Unset clock");
    return status;
}

/**
 * @brief Execute UnsetClock command
 *
 * @return true successful
 * @return false error
 */

bool CommandUnsetClock::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("Unset clock");
    extern AvionicsBoard avionics;
    status = avionics.unset_clock() && status;
    auto response{Response{status ? "URC" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge ReportT command
 *
 * @return true successful
 * @return false error
 */

bool CommandReportT::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("ReportT");
    return status;
}

/**
 * @brief Execute ReportT command
 *
 * @return true successful
 * @return false error
 */

bool CommandReportT::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("ReportT");
    extern AvionicsBoard avionics;
    auto timestamp{avionics.get_timestamp()};
    if (timestamp == "ERROR")
        status = false;
    auto response{Response{status ? ("GRC " + timestamp) : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge GetPicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPicTimes::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("GetPicTimes");
    return status;
}

/**
 * @brief  Execute GetPicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPicTimes::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("GetPicTimes");
    extern AvionicsBoard avionics;
    auto response{Response{status ? ("GPT " + avionics.get_pic_times()) : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge GetTelemetry command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetTelemetry::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("GetTelemetry");
    return status;
}

/**
 * @brief  Execute GetTelemetry command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetTelemetry::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("GetTelemetry");
    extern AvionicsBoard avionics;
    auto response{Response{status ? ("GTY" + avionics.get_telemetry()) : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge GetPower command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPower::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("GetPower");
    return status;
}

/**
 * @brief  Execute GetPower command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPower::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("GetPower");
    extern PowerBoard power;
    auto response{Response{status ? ("GPW" + power.get_detail()) : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge GetComms command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetComms::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("GetComms");
    return status;
}

/**
 * @brief  Execute GetComms command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetComms::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("GetComms");
    Log.traceln("Requesting radio status");
    Message message(Message::get_status, "");
    return message.send() && status;
}

/**
 * @brief Acknowledge GetBeaconInterval command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetBeaconInterval::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("GetBeaconInterval");
    return status;
}

/**
 * @brief  Execute GetBeaconInterval command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetBeaconInterval::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("GetBeaconInterval");
    extern AvionicsBoard avionics;
    auto response{Response{status ? ("GBI " + avionics.get_beacon_interval()) : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge NoOperate command
 *
 * @return true successful
 * @return false error
 */

bool CommandNoOperate::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("NoOperate");
    return status;
}

/**
 * @brief Execute NoOperate command
 *
 * @return true successful
 * @return false error
 */

bool CommandNoOperate::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("NoOperate");
    auto response{Response{status ? "NOP" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge SendTestPacket command
 *
 * @return true successful
 * @return false error
 */

bool CommandSendTestPacket::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("SendTestPacket");
    return status;
}

/**
 * @brief Execute SendTestPacket command
 *
 * @return true successful
 * @return false error
 */

bool CommandSendTestPacket::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("SendTestPacket");
    auto response{Response{status ? "STP test packet" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge PayComms command
 *
 * @return true successful
 * @return false error
 */

bool CommandPayComms::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("PayComms");
    return status;
}

/**
 * @brief Execute PayComms command
 *
 * @return true successful
 * @return false error
 */

bool CommandPayComms::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("PayComms");
    extern PayloadBoard payload;
    status = payload.communicate() && status;
    auto response{Response{status ? "PYC" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge TweeSlee command
 *
 * @return true successful
 * @return false error
 */

bool CommandTweeSlee::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("TweeSlee");
    return status;
}

/**
 * @brief Execute TweeSlee command
 *
 * @return true successful
 * @return false error
 */

bool CommandTweeSlee::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("TweeSlee");
    auto response{Response{status ? "TSL" : "ERR"}};
    status = response.send() && status;
    extern PayloadBoard payload;
    Log.traceln("Turning off payload power");
    status = payload.power_down() && status;
    Log.traceln("Sending local command: halt");
    auto message{Message(Message::halt, "")};
    return message.send() && status;
}

/**
 * @brief Acknowledge Watchdog command
 *
 * @return true successful
 * @return false error
 */

bool CommandWatchdog::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("Watchdog");
    return status;
}

/**
 * @brief Execute Watchdog command
 *
 * @return true successful
 * @return false error
 */
bool CommandWatchdog::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("Watchdog");
    auto response{Response{status ? "WDG" : "ERR"}};
    status = response.send() && status;
    extern AvionicsBoard avionics;
    avionics.watchdog_force_reset();
    return status;
}

/**
 * @brief Acknowledge invalid command
 *
 * @return false error
 */

bool CommandInvalid::acknowledge_command()
{
    Command::negative_acknowledge_command();
    Log.verboseln("Invalid");
    return false;
}

/**
 * @brief Execute invalid command
 *
 * @return false error
 */

bool CommandInvalid::execute_command()
{
    Log.errorln("Cannot execute invalid command");
    return false;
}

/**
 * @brief Acknowledge unknown command
 *
 * @return false error
 */

bool CommandUnknown::acknowledge_command()
{
    Command::negative_acknowledge_command();
    Log.verboseln("Unknown");
    return false;
}

/**
 * @brief Execute unknown command
 *
 * @return false error
 */

bool CommandUnknown::execute_command()
{
    Log.errorln("Cannot execute unknown command");
    return false;
}

/**
 * @brief Acknowledge ModifyMode command
 *
 * @return true successful
 * @return false error
 */

bool CommandModifyMode::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("ModifyMode");
    return status;
}

/**
 * @brief Execute ModifyMode command
 *
 * @return true successful
 * @return false error
 */

bool CommandModifyMode::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("ModifyMode");
    Message message(Message::modify_mode, String(m_mode));
    Log.traceln("Requesting mode modification");
    return message.send() && status;
}
