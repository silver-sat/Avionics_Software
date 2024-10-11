/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 *
 * This file implements the acknowledge and execute methods for all Command objects.
 * Virtual dispatch is used to select the correct methods based on command type. Each
 * derived Command calls the base class acknowledgement method for sending an
 * acknowledgement to the ground and the base execute method for logging. Abbreviations
 * listed are used in command responses.
 *
 * Change satellite state:
 *
 * SRC: SetClock: subsumes SetTime: set realtime clock
 * SBI: BeaconSp: set beacon spacing
 * SPT: PicTimes: set times for photos
 * SST: SSDVTimes: set times for SSDV broadcasts
 * CPQ: ClearPayloadQueue: empty payload activity queue
 * URC: UnsetClock: change the realtime clock status to unset for testing
 *
 * Get satellite state:
 *
 * GRC: ReportT: subsumes GetTime: reply with realtime clock setting
 * GPQ: GetPayloadQueue: reply with payload schedule
 * GTY: GetTelemetry: reply with telemetry
 * GPW: GetPower: reply with power status
 * GRS: GetComms: reply with Radio Board status
 * GBI: GetBeaconInterval: reply with beacon interval
 *
 * Invoke satellite operation:
 *
 * NOP: NoOperate: subsumes Ping: acknowledge
 * STP: SendTestPacket: reply with test message
 * PYC: PayComms: subsumes Begin tweet : start payload in communications mode
 * TSL: TweeSlee: subsumes Halt: stop communicating
 * WDG: Watchdog: force watchdog timeout (reset SAMD21)
 *
 * Invalid and unknown commands
 *
 * INV: invalid
 * UNK: unknown
 *
 * Radio commands:
 *
 * RMM: ModifyMode: modify radio mode
 *
 * Deprecated commands:
 *
 * halt, see TweeSlee
 * s_call_sig deprecated
 * g_call_sig, deprecated
 * GPC: GetPhotos: reply with number of photos (Avionics Board does not have an accurate count)
 * RMF: ModifyFrequency: modify radio frequency
 * RAF: AdjustFrequency: adjust radio frequency temporarily
 * RTC: TransmitCW: transmit carrier wave
 * RBR: BackgroundRSSI: radio background rssi
 * RCR: CurrentRSSI: radio current rssi
 * RST: SweepTransmitter: radio sweep transmitter
 * RSR: SweepReceiver: radio sweep receiver
 * RQR: QueryRegister: radio query register
 * CPT: ClearPicTimes: replaced with ClearPayloadQueue
 * CST: ClearSSDVTimes: replaced with ClearPayloadQueue
 * GPT: GetPicTimes: replaced with GetPayloadQueue
 * GST: GetSSDVTimes: replaced with GetPayloadQueue


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
 * @brief Acknowlege SSDVTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandSSDVTimes::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("SSDVTimes: Year: %d Month: %d Day: %d Hour: %d Minute: %d Second: %d",
                  m_time.year(), m_time.month(), m_time.day(), m_time.hour(), m_time.minute(), m_time.second());
    return status;
}

/**
 * @brief Execute SSDVTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandSSDVTimes::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("SSDVTimes");
    extern AvionicsBoard avionics;
    status = avionics.set_SSDV_time(m_time) && status;
    auto response{Response{status ? "SST" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge ClearPayloadQueue command
 *
 * @return true successful
 * @return false error
 */

bool CommandClearPayloadQueue::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("ClearPayloadQueue");
    return status;
}

/**
 * @brief Execute ClearPayloadQueue command
 *
 * @return true successful
 * @return false error
 */

bool CommandClearPayloadQueue::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("ClearPayloadQueue");
    extern AvionicsBoard avionics;
    status = avionics.clear_payload_queue() && status;
    auto response{Response{status ? "CPQ" : "ERR"}};
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
 * @brief Acknowledge GetPayloadQueue command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPayloadQueue::acknowledge_command()
{
    auto status{Command::acknowledge_command()};
    Log.verboseln("GetPayloadfQueue");
    return status;
}

/**
 * @brief  Execute GetPayloadQueue command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPayloadQueue::execute_command()
{
    auto status{Command::execute_command()};
    Log.verboseln("GetPayloadQueue");
    extern AvionicsBoard avionics;
    auto response{Response{status ? ("GPQ " + String{avionics.get_payload_queue_size()} + " entries in queue") : "ERR"}};
    status = response.send() && status;
    for (auto i{0}; i < avionics.get_payload_queue_size(); i++)
    {
        String element = String{i} + " " + avionics.m_payload_queue[i].time.timestamp() + " " + avionics.m_payload_queue[i].type;
        auto response{Response{status ? ("GPQ " + element) : "ERR"}};
        status = response.send() && status;
    }
    return status;
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
