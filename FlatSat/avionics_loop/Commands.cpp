/**
 * @file Commands.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 * @version 1.3.0
 * @date 2022-07-25
 *
 *
 */

#include "Commands.h"
#include "Message.h"
#include "log_utility.h"
#include "AvionicsBoard.h"
#include "PowerBoard.h"
#include "RadioBoard.h"
#include "PayloadBoard.h"

/**
 * @brief Acknowledge the command
 *
 */

bool Command::acknowledge_command()
{
    Log.traceln("Acknowledging command");
    Message message{Message::acknowledgement, "ACK"};
    extern RadioBoard radio;
    return radio.send_message(message);
};

/**
 * @brief Negative acknowledge the command
 *
 */

bool Command::negative_acknowledge_command()
{
    Log.traceln("Negative acknowledging command");
    Message message{Message::negative_acknowledgement, "NACK"};
    extern RadioBoard radio;
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
 * @brief Acknowledge unknown command
 *
 * @return false error
 */

bool CommandUnknown::acknowledge_command()
{
    Command::negative_acknowledge_command();
    Log.verboseln("Unknown");
    return false;
};

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
 * @brief Acknowledge invalid command
 *
 * @return false error
 */

bool CommandInvalid::acknowledge_command()
{
    Command::negative_acknowledge_command();
    Log.verboseln("Invalid");
    return false;
};

/**
 * @brief Execute invalid command
 *
 * @return false error
 */
bool CommandInvalid::execute_command()
{
    Log.errorln("Cannot execute invalid command");
    return false;
};

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
};

/**
 * @brief Execute NoOperate command
 *
 * @return true successful
 */

bool CommandNoOperate::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("NoOperate");
    extern RadioBoard radio;
    auto message{Message(Message::response, "NOP")};
    return radio.send_message(message) && status;
};

/**
 * @brief Acknowledge PayComms command
 *
 */

bool CommandPayComms::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("PayComms");
    return status;
};

bool CommandPayComms::execute_command()
{

    auto status{Command::execute_command()};
    Log.verboseln("PayComms");
    extern RadioBoard radio;
    auto message{Message(Message::response, "PYC")};
    status = radio.send_message(message) && status;
    extern PayloadBoard payload;
    return payload.tweet() && status;
};

/**
 * @brief Acknowledge ReportT command
 *
 */

bool CommandReportT::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("ReportT");
    return status;
};

bool CommandReportT::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("ReportT");
    extern AvionicsBoard avionics;
    auto timestamp{avionics.get_timestamp()};
    if (timestamp == "ERROR")
    {
        status = false;
    };
    extern RadioBoard radio;
    auto message = Message(Message::response, timestamp);
    return radio.send_message(message) && status;
};

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
};

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
    extern RadioBoard radio;
    auto message{Message(Message::response, "RESTSL")};
    status = radio.send_message(message) && status;
    extern PayloadBoard payload;
    Log.traceln("Turning off payload power");
    status = payload.power_down() && status;
    Log.traceln("Sending local command: halt");
    message = Message(Message::halt, "");
    return radio.send_message(message) && status;
};

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
};

bool CommandWatchdog::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("Watchdog");
    extern RadioBoard radio;
    auto message{Message(Message::response, "WDG")};
    status = radio.send_message(message) && status;
    extern AvionicsBoard avionics;
    avionics.watchdog_force_reset();
    return status;
};

/**
 * @brief Acknowledge BeaconSp command
 *
 * @return true
 * @return false
 */

bool CommandBeaconSp::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("BeaconSp: %d seconds", m_seconds);
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
    auto status{Command::execute_command()};
    Log.verboseln("BeaconSp");
    extern RadioBoard radio;
    auto message{Message(Message::response, "SBS")};
    status = radio.send_message(message) && status;
    extern AvionicsBoard avionics;
    return avionics.set_beacon_interval(m_seconds) && status;
};

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
    extern RadioBoard radio;
    auto message{Message(Message::response, "SPT")};
    status = radio.send_message(message) && status;
    extern AvionicsBoard avionics;
    return avionics.set_picture_time(m_time) && status;
};

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
    extern RadioBoard radio;
    auto message{Message(Message::response, "SRC")};
    status = radio.send_message(message) && status;
    extern AvionicsBoard avionics;
    return avionics.set_external_rtc(m_time) && status;
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
};

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
    extern RadioBoard radio;
    auto message{Message(Message::response, avionics.get_pic_times())};
    return radio.send_message(message) && status;
};

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
};

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
    extern RadioBoard radio;
    auto message{Message(Message::response, avionics.get_telemetry())};
    return radio.send_message(message) && status;
};

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
};

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
    extern RadioBoard radio;
    auto message{Message(Message::response, power.get_detail())};
    return radio.send_message(message) && status;
};

/**
 * @brief Acknowledge GetPhotos command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPhotos::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
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
    auto status{Command::execute_command()};
    Log.verboseln("GetPhotos");
    extern PayloadBoard payload;
    extern RadioBoard radio;
    auto message{Message(Message::response, String(payload.get_photo_count()).c_str())};
    return radio.send_message(message) && status;
};

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
};

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
    extern RadioBoard radio;
    // todo: get status before response
    auto message{Message(Message::response, radio.get_status().c_str())};
    return radio.send_message(message) && status;
};

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
};

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
    extern RadioBoard radio;
    auto message{Message(Message::response, String(avionics.get_beacon_interval()).c_str())};
    return radio.send_message(message) && status;
};

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
};

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
    extern RadioBoard radio;
    auto message = Message(Message::response, "TEST");
    return radio.send_message(message) && status;
};

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
};

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
    extern RadioBoard radio;
    auto message{Message(Message::response, "RESCPT")};
    status = radio.send_message(message) && status;
    extern AvionicsBoard avionics;
    return avionics.clear_pic_times() && status;
};

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
    extern RadioBoard radio;
    auto message{Message(Message::response, "URC")};
    status = radio.send_message(message) && status;
    extern AvionicsBoard avionics;
    return avionics.unset_clock() && status;
}