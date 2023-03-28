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
#include "RadioBoard.h"
#include "PayloadBoard.h"

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
    Message message{Message::acknowledgement, ACK};
    extern RadioBoard radio;
    return radio.send_message(message);
};

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
    Message message{Message::negative_acknowledgement, NACK};
    extern RadioBoard radio;
    return radio.send_message(message);
};

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
    auto response{Response{"SRC"}};
    status = radio.send_message(response) && status;
    extern AvionicsBoard avionics;
    return avionics.set_external_rtc(m_time) && status;
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
};

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
    extern RadioBoard radio;
    auto response{Response{"SBI"}};
    status = radio.send_message(response) && status;
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
    auto response{Response{"SPT"}};
    status = radio.send_message(response) && status;
    extern AvionicsBoard avionics;
    return avionics.set_picture_time(m_time) && status;
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
    auto response{Response{"CPT"}};
    status = radio.send_message(response) && status;
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
    auto response{Response{"URC"}};
    status = radio.send_message(response) && status;
    extern AvionicsBoard avionics;
    return avionics.unset_clock() && status;
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
};

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
    {
        status = false;
    };
    extern RadioBoard radio;
    auto response{Response{"GRC" + timestamp}};
    return radio.send_message(response) && status;
};

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
    auto response{Response{"GPT" + avionics.get_pic_times()}};
    return radio.send_message(response) && status;
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
    auto response{Response{"GTY" + avionics.get_telemetry()}};
    return radio.send_message(response) && status;
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
    auto response{Response{"GPW" + power.get_detail()}};
    return radio.send_message(response) && status;
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
    Message message(Message::get_status, "");
    Log.verboseln("Requesting radio status");
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
    auto response{Response{"GBI" + String(avionics.get_beacon_interval())}};
    return radio.send_message(response) && status;
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
 * @return false error
 */

bool CommandNoOperate::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("NoOperate");
    extern RadioBoard radio;
    auto response{Response{"NOP"}};
    return radio.send_message(response) && status;
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
    auto response{Response{"STPTEST"}};
    return radio.send_message(response) && status;
};

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
};

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
    extern RadioBoard radio;
    auto response{Response{"PYC"}};
    status = radio.send_message(response) && status;
    extern PayloadBoard payload;
    return payload.communicate() && status;
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
    auto response{Response{"TSL"}};
    status = radio.send_message(response) && status;
    extern PayloadBoard payload;
    Log.traceln("Turning off payload power");
    status = payload.power_down() && status;
    Log.traceln("Sending local command: halt");
    auto message{Message(Message::halt, "")};
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
    extern RadioBoard radio;
    auto response{Response{"WDG"}};
    status = radio.send_message(response) && status;
    extern AvionicsBoard avionics;
    avionics.watchdog_force_reset();
    return status;
};

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
 * @brief Acknowledge ModifyFrequency command
 *
 * @return true successful
 * @return false error
 */

bool CommandModifyFrequency::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("ModifyFrequency");
    return status;
}

/**
 * @brief Execute ModifyFrequency command
 *
 * @return true successful
 * @return false error
 */

bool CommandModifyFrequency::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("ModifyFrequency");
    extern RadioBoard radio;
    Message message(Message::modify_frequency, String{m_frequency});
    Log.verboseln("Requesting frequency modification");
    return radio.send_message(message) && status;
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
    extern RadioBoard radio;
    Message message(Message::modify_mode, String(m_mode));
    Log.verboseln("Requesting mode modification");
    return radio.send_message(message) && status;
}

/**
 * @brief Acknowledge AdjustFrequency command
 *
 * @return true successful
 * @return false error
 */

bool CommandAdjustFrequency::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("AdjustFrequency");
    return status;
}

/**
 * @brief Execute AdjustFrequency command
 *
 * @return true successful
 * @return false error
 */

bool CommandAdjustFrequency::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("AdjustFrequency");
    extern RadioBoard radio;
    Message message(Message::adjust_frequency, String{m_frequency});
    Log.verboseln("Requesting frequency adjustment");
    return radio.send_message(message) && status;
}

/**
 * @brief Acknowledge TransmitCW command
 *
 * @return true successful
 * @return false error
 */

bool CommandTransmitCW::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("TransmitCW");
    return status;
}

/**
 * @brief Execute TransmitCW command
 *
 * @return true successful
 * @return false error
 */

bool CommandTransmitCW::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("TransmitCW");
    extern RadioBoard radio;
    Message message(Message::transmit_cw, String{m_duration});
    Log.verboseln("Requesting carrier wave");
    return radio.send_message(message) && status;
}

/**
 * @brief Acknowledge BackgroundRSSI command
 *
 * @return true successful
 * @return false error
 */

bool CommandBackgroundRSSI::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("BackgroundRSSI");
    return status;
}

/**
 * @brief Execute BackgroundRSSI command
 *
 * @return true successful
 * @return false error
 */

bool CommandBackgroundRSSI::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("BackgroundRSSI");
    extern RadioBoard radio;
    Message message{Message::background_rssi, ""};
    Log.verboseln("Requesting background RSSI");
    return radio.send_message(message) && status;
}

/**
 * @brief Acknowledge CurrentRSSI command
 *
 * @return true successful
 * @return false error
 */

bool CommandCurrentRSSI::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("CurrentRSSI");
    return status;
}

/**
 * @brief Execute CurrentRSSI command
 *
 * @return true successful
 * @return false error
 */

bool CommandCurrentRSSI::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("CurrentRSSI");
    extern RadioBoard radio;
    Message message(Message::current_rssi, "");
    Log.verboseln("Requesting current RSSI");
    return radio.send_message(message) && status;
}

/**
 * @brief Acknowledge SweepTransmitter command
 *
 * @return true successful
 * @return false error
 */

bool CommandSweepTransmitter::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("SweepTransmitter");
    return status;
}

/**
 * @brief Execute SweepTransmitter command
 *
 * @return true successful
 * @return false error
 */

bool CommandSweepTransmitter::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("SweepTransmitter");
    extern RadioBoard radio;
    char arguments[frequency_length + frequency_length + steps_length + dwell_length + 1]{};
    char *arg_ptr{};
    arg_ptr = &arguments[0];
    memcpy(arg_ptr, m_start_frequency, frequency_length);
    arg_ptr += frequency_length;
    memcpy(arg_ptr, m_stop_frequency, frequency_length);
    arg_ptr += frequency_length;
    memcpy(arg_ptr, m_number_of_steps, steps_length);
    arg_ptr += steps_length;
    memcpy(arg_ptr, m_dwell_time, dwell_length);
    arg_ptr += steps_length;
    *arg_ptr = '\0';
    Message message{Message::sweep_tranmitter, String{arguments}};
    Log.verboseln("Requesting transmitter sweep");
    return radio.send_message(message) && status;
}

/**
 * @brief Acknowledge SweepReceiver command
 *
 * @return true successful
 * @return false error
 */

bool CommandSweepReceiver::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("SweepReceiver");
    return status;
}

/**
 * @brief Execute SweepReceiver command
 *
 * @return true successful
 * @return false error
 */

bool CommandSweepReceiver::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("SweepReceiver");
    extern RadioBoard radio;
    char arguments[frequency_length + frequency_length + steps_length + dwell_length + 1]{};
    char *arg_ptr{};
    arg_ptr = &arguments[0];
    memcpy(arg_ptr, m_start_frequency, frequency_length);
    arg_ptr += frequency_length;
    memcpy(arg_ptr, m_stop_frequency, frequency_length);
    arg_ptr += frequency_length;
    memcpy(arg_ptr, m_number_of_steps, steps_length);
    arg_ptr += steps_length;
    memcpy(arg_ptr, m_dwell_time, dwell_length);
    arg_ptr += steps_length;
    *arg_ptr = '\0';
    Message message{Message::sweep_receiver, String{arguments}};
    Log.verboseln("Requesting receiver sweep");
    return radio.send_message(message) && status;
}

/**
 * @brief Acknowledge QueryRegister command
 *
 * @return true successful
 * @return false error
 */

bool CommandQueryRegister::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("QueryRegister");
    return status;
}

/**
 * @brief Execute QueryRegister command
 *
 * @return true successful
 * @return false error
 */

bool CommandQueryRegister::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("QueryRegister");
    extern RadioBoard radio;
    Message message(Message::query_register, String{m_radio_register});
    Log.verboseln("Requesting radio register");
    return radio.send_message(message) && status;
}