/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 *
 * This file implements the methods for all Command objects.
 * Virtual dispatch is used to select the correct methods based on command type.
 * Each derived command validates arguments. If data is required, it is loaded.
 * Each
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
 * PYC: PayComms: subsumes Begin tweet : start payload in communications mode
 * TSL: TweeSlee: subsumes Halt: stop communicating
 * WDG: Watchdog: force watchdog timeout (reset SAMD21)
 *
 * Invalid and unknown commands
 *
 * INV: invalid
 * UNK: unknown
 *
 * Test Commands
 *
 * NOP: NoOperate: subsumes Ping: acknowledge
 * STP: SendTestPacket: reply with test message
 * URC: UnsetClock: change the realtime clock status to unset for testing
 * LCA: LogArguments: Log command arguments with no acknowledgement or response
 * RBR: BackgroundRSSI: radio background RSSI
 * RCR: CurrentRSSI: radio current RSSI
 * RMC: ModifyCCA: Modify CCA threshold
 *
 * Deprecated commands:
 *
 * halt, see TweeSlee
 * s_call_sig deprecated
 * g_call_sig, deprecated
 * GPC: GetPhotos: reply with number of photos (Avionics Board does not have an accurate count)
 * RAF: AdjustFrequency: adjust radio frequency temporarily
 * RTC: TransmitCW: transmit carrier wave
 * RST: SweepTransmitter: radio sweep transmitter
 * RSR: SweepReceiver: radio sweep receiver
 * RQR: QueryRegister: radio query register
 * CPT: ClearPicTimes: replaced with ClearPayloadQueue
 * GPT: GetPicTimes: replaced with GetPayloadQueue
 * RMF: ModifyFrequency: modify radio frequency
 * RMM: ModifyMode: modify radio mode
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

const String Command::m_action{"Command"};
const String CommandSetClock::m_action{"Set realtime clock"};
const String CommandBeaconSp::m_action{"Set beacon spacing"};
const String CommandPicTimes::m_action{"Set picture times"};
const String CommandSSDVTimes::m_action{"Set SSDV times"};
const String CommandClearPayloadQueue::m_action{"Clear payload queue"};
const String CommandReportT::m_action{"Report time"};
const String CommandGetPayloadQueue::m_action{"Get payload queue"};
const String CommandGetTelemetry::m_action{"Get telemetry"};
const String CommandGetPower::m_action{"Get power data"};
const String CommandGetComms::m_action{"Get radio status"};
const String CommandGetBeaconInterval::m_action{"Get beacon interval"};
const String CommandPayComms::m_action{"Payload communications"};
const String CommandTweeSlee::m_action{"Payload halt"};
const String CommandWatchdog::m_action{"Force watchdog reset"};
const String CommandInvalid::m_action{"Invalid command"};
const String CommandUnknown::m_action{"Unknown command"};
const String CommandNoOperate::m_action{"No operate"};
const String CommandSendTestPacket::m_action{"Send test packet"};
const String CommandUnsetClock::m_action{"Unset reatime clock"};
const String CommandLogArguments::m_action{"Log command arguments"};
const String CommandBackgroundRSSI::m_action("Report background RSSI");
const String CommandCurrentRSSI::m_action("Report current RSSI");
const String CommandModifyCCA::m_action("Modify CCA threshold");

/**
 * @brief Helper function to determine if a string is numeric
 *
 */

bool is_numeric(const String &str)
{
    for (auto i{0}; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Helper function to validate a date
 *
 */

bool is_valid_time(const String tokens[], const size_t token_count)
{
    if (token_count != 7)
    {
        return false;
    }
    if (!is_numeric(tokens[1]) || !is_numeric(tokens[2]) || !is_numeric(tokens[3]) || !is_numeric(tokens[4]) || !is_numeric(tokens[5]) || !is_numeric(tokens[6]))
    {
        return false;
    }
    long year = tokens[1].toInt();
    if (year < minimum_valid_year || year > maximum_valid_year)
    {
        return false;
    }
    long month = tokens[2].toInt();
    if (month < 1 || month > 12)
    {
        return false;
    }
    // todo: add check for valid days in month
    long day = tokens[3].toInt();
    if (day < 1 || day > 31)
    {
        return false;
    }
    long hour = tokens[4].toInt();
    if (hour < 0 || hour > 23)
    {
        return false;
    }
    long minute = tokens[5].toInt();
    if (minute < 0 || minute > 59)
    {
        return false;
    }
    long second = tokens[6].toInt();
    if (second < 0 || second > 59)
    {
        return false;
    }
    return true;
}

/**
 * @brief Validate the arguments
 *
 * @return true successful
 * @return false error
 *
 * Validate arguments
 *
 */

bool Command::validate_arguments(const String tokens[], const size_t token_count) const
{
    Log.traceln("Validating %d argument(s) for: %s", token_count - 1, tokens[0].c_str());
    if (token_count < 2)
    {
        return true;
    }
    return false;
}

/**
 * @brief Load command data
 *
 * @return true successful
 * @return false error
 *
 * Load command data
 *
 */

bool Command::load_data(const String tokens[], const size_t token_count)
{
    Log.traceln("No data to load for: %s", tokens[0].c_str());
    return true;
}

/**
 * @brief Acknowledge the command
 *
 * @return true successful
 * @return false error
 *
 * Send acknowledgement to the ground
 *
 */

bool Command::acknowledge_receipt() const
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

bool Command::negative_acknowledge_receipt() const
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

bool Command::execute() const
{
    Log.traceln("Executing command");
    return true;
}

/**
 * @brief Validate arguments for SetClock command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandSetClock::validate_arguments(const String tokens[], const size_t token_count) const
{
    Log.traceln("Validating %d argument(s) for: %s", token_count - 1, tokens[0].c_str());
    return is_valid_time(tokens, token_count);
}

/**
 * @brief Load arguments for SetClock command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandSetClock::load_data(const String tokens[], const size_t token_count)
{
    Log.traceln("Loading arguments for: %s", tokens[0].c_str());
    uint16_t year = static_cast<uint16_t>(tokens[1].toInt());
    uint8_t month = static_cast<uint8_t>(tokens[2].toInt());
    uint8_t day = static_cast<uint8_t>(tokens[3].toInt());
    uint8_t hour = static_cast<uint8_t>(tokens[4].toInt());
    uint8_t minute = static_cast<uint8_t>(tokens[5].toInt());
    uint8_t second = static_cast<uint8_t>(tokens[6].toInt());

    m_time = DateTime{year, month, day, hour, minute, second};
    return true;
}

/**
 * @brief Acknowlege SetClock command
 *
 * @return true successful
 * @return false error
 */

bool CommandSetClock::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
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

bool CommandSetClock::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("SetClock");
    extern AvionicsBoard avionics;
    status = avionics.set_external_rtc(m_time) && status;
    auto response{Response{status ? "SRC" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Validate arguments for BeaconSp command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandBeaconSp::validate_arguments(const String tokens[], const size_t token_count) const
{
    Log.traceln("Validating %d argument(s) for: %s", token_count - 1, tokens[0].c_str());
    if (token_count != 2)
    {
        return false;
    }
    if (!is_numeric(tokens[1]))
    {
        return false;
    }
    long seconds = tokens[1].toInt();
    if (seconds == 0)
    {
        return true; // zero turns off the beacon
    }
    if (seconds < minimum_beacon_interval || seconds > maximum_beacon_interval)
    {
        return false;
    }
    return true;
}

/**
 * @brief Load argument for BeaconSp command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandBeaconSp::load_data(const String tokens[], const size_t token_count)
{
    Log.traceln("Loading argument for: %s", tokens[0].c_str());
    m_seconds = tokens[1].toInt();
    return true;
}

/**
 * @brief Acknowledge BeaconSp command
 *
 * @return true successful
 * @return false error
 */

bool CommandBeaconSp::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("BeaconSp: %d seconds", m_seconds);
    return status;
}

/**
 * @brief Execute BeaconSp command
 *
 * @return true successful
 * @return false error
 */

bool CommandBeaconSp::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("BeaconSp");
    extern AvionicsBoard avionics;
    status = avionics.set_beacon_interval(m_seconds) && status;
    auto response{Response{status ? "SBI" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Valiidate arguments for PicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandPicTimes::validate_arguments(const String tokens[], const size_t token_count) const
{
    Log.traceln("Validating %d argument(s) for: %s", token_count - 1, tokens[0].c_str());
    return is_valid_time(tokens, token_count);
}

/**
 * @brief Load arguments for PicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandPicTimes::load_data(const String tokens[], const size_t token_count)
{
    Log.traceln("Loading arguments for: %s", tokens[0].c_str());
    uint16_t year = static_cast<uint16_t>(tokens[1].toInt());
    uint8_t month = static_cast<uint8_t>(tokens[2].toInt());
    uint8_t day = static_cast<uint8_t>(tokens[3].toInt());
    uint8_t hour = static_cast<uint8_t>(tokens[4].toInt());
    uint8_t minute = static_cast<uint8_t>(tokens[5].toInt());
    uint8_t second = static_cast<uint8_t>(tokens[6].toInt());

    m_time = DateTime{year, month, day, hour, minute, second};
    return true;
}

/**
 * @brief Acknowlege PicTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandPicTimes::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
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

bool CommandPicTimes::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("PicTimes");
    extern AvionicsBoard avionics;
    status = avionics.set_picture_time(m_time) && status;
    auto response{Response{status ? "SPT" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Validate arguments for SSDVTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandSSDVTimes::validate_arguments(const String tokens[], const size_t token_count) const
{
    Log.traceln("Validating %d argument(s) for: %s", token_count - 1, tokens[0].c_str());
    return is_valid_time(tokens, token_count);
}

/**
 * @brief Load arguments for SSDVTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandSSDVTimes::load_data(const String tokens[], const size_t token_count)
{
    Log.traceln("Loading arguments for: %s", tokens[0].c_str());
    uint16_t year = static_cast<uint16_t>(tokens[1].toInt());
    uint8_t month = static_cast<uint8_t>(tokens[2].toInt());
    uint8_t day = static_cast<uint8_t>(tokens[3].toInt());
    uint8_t hour = static_cast<uint8_t>(tokens[4].toInt());
    uint8_t minute = static_cast<uint8_t>(tokens[5].toInt());
    uint8_t second = static_cast<uint8_t>(tokens[6].toInt());

    m_time = DateTime{year, month, day, hour, minute, second};
    return true;
}

/**
 * @brief Acknowlege SSDVTimes command
 *
 * @return true successful
 * @return false error
 */

bool CommandSSDVTimes::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
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

bool CommandSSDVTimes::execute() const
{
    auto status{Command::execute()};
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

bool CommandClearPayloadQueue::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("ClearPayloadQueue");
    return status;
}

/**
 * @brief Execute ClearPayloadQueue command
 *
 * @return true successful
 * @return false error
 */

bool CommandClearPayloadQueue::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("ClearPayloadQueue");
    extern AvionicsBoard avionics;
    status = avionics.clear_payload_queue() && status;
    auto response{Response{status ? "CPQ" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge ReportT command
 *
 * @return true successful
 * @return false error
 */

bool CommandReportT::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("ReportT");
    return status;
}

/**
 * @brief Execute ReportT command
 *
 * @return true successful
 * @return false error
 */

bool CommandReportT::execute() const
{
    auto status{Command::execute()};
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

bool CommandGetPayloadQueue::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("GetPayloadfQueue");
    return status;
}

/**
 * @brief  Execute GetPayloadQueue command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPayloadQueue::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("GetPayloadQueue");
    extern AvionicsBoard avionics;
    auto response{Response{status ? ("GPQ " + String{avionics.get_payload_queue_size()} + " entries in queue") : "ERR"}};
    status = response.send() && status;
    for (auto i{0}; i < avionics.get_payload_queue_size(); i++)
    {
        String element = String{i} + " " + avionics.m_payload_queue[i].time.timestamp() + " " + PayloadQueue::activity_name(avionics.m_payload_queue[i].type);
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

bool CommandGetTelemetry::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("GetTelemetry");
    return status;
}

/**
 * @brief  Execute GetTelemetry command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetTelemetry::execute() const
{
    auto status{Command::execute()};
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

bool CommandGetPower::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("GetPower");
    return status;
}

/**
 * @brief  Execute GetPower command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetPower::execute() const
{
    auto status{Command::execute()};
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

bool CommandGetComms::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("GetComms");
    return status;
}

/**
 * @brief  Execute GetComms command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetComms::execute() const
{
    auto status{Command::execute()};
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

bool CommandGetBeaconInterval::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("GetBeaconInterval");
    return status;
}

/**
 * @brief  Execute GetBeaconInterval command
 *
 * @return true successful
 * @return false error
 */

bool CommandGetBeaconInterval::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("GetBeaconInterval");
    extern AvionicsBoard avionics;
    auto response{Response{status ? ("GBI " + avionics.get_beacon_interval()) : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge PayComms command
 *
 * @return true successful
 * @return false error
 */

bool CommandPayComms::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("PayComms");
    return status;
}

/**
 * @brief Execute PayComms command
 *
 * @return true successful
 * @return false error
 */

bool CommandPayComms::execute() const
{
    auto status{Command::execute()};
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

bool CommandTweeSlee::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("TweeSlee");
    return status;
}

/**
 * @brief Execute TweeSlee command
 *
 * @return true successful
 * @return false error
 */

bool CommandTweeSlee::execute() const
{
    auto status{Command::execute()};
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

bool CommandWatchdog::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("Watchdog");
    return status;
}

/**
 * @brief Execute Watchdog command
 *
 * @return true successful
 * @return false error
 */
bool CommandWatchdog::execute() const
{
    auto status{Command::execute()};
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

bool CommandInvalid::acknowledge_receipt() const
{
    Command::negative_acknowledge_receipt();
    Log.verboseln("Invalid");
    return false;
}

/**
 * @brief Execute invalid command
 *
 * @return false error
 */

bool CommandInvalid::execute() const
{
    Log.errorln("Cannot execute invalid command");
    return false;
}

/**
 * @brief Acknowledge unknown command
 *
 * @return false error
 */

bool CommandUnknown::acknowledge_receipt() const
{
    Command::negative_acknowledge_receipt();
    Log.verboseln("Unknown");
    return false;
}

/**
 * @brief Execute unknown command
 *
 * @return false error
 */

bool CommandUnknown::execute() const
{
    Log.errorln("Cannot execute unknown command");
    return false;
}

/**
 * @brief Acknowledge NoOperate command
 *
 * @return true successful
 * @return false error
 */

bool CommandNoOperate::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("NoOperate");
    return status;
}

/**
 * @brief Execute NoOperate command
 *
 * @return true successful
 * @return false error
 */

bool CommandNoOperate::execute() const
{
    auto status{Command::execute()};
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

bool CommandSendTestPacket::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("SendTestPacket");
    return status;
}

/**
 * @brief Execute SendTestPacket command
 *
 * @return true successful
 * @return false error
 */

bool CommandSendTestPacket::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("SendTestPacket");
    auto response{Response{status ? "STP test packet" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Acknowledge UnsetClock command
 *
 * @return true successful
 * @return false error
 */

bool CommandUnsetClock::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("Unset clock");
    return status;
}

/**
 * @brief Execute UnsetClock command
 *
 * @return true successful
 * @return false error
 */

bool CommandUnsetClock::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("Unset clock");
    extern AvionicsBoard avionics;
    status = avionics.unset_clock() && status;
    auto response{Response{status ? "URC" : "ERR"}};
    return response.send() && status;
}

/**
 * @brief Validate arguments for LogArguments command
 *
 * @return true successful
 * @return false error
 *
 * Validate arguments
 *
 */

bool CommandLogArguments::validate_arguments(const String tokens[], const size_t token_count) const
{
    Log.traceln("%d arguments for: %s", token_count - 1, tokens[0].c_str());
    return true;
}

/**
 * @brief Load arguments for LogArguments command
 *
 * @return true successful
 * @return false error
 *
 * Load command data
 *
 */

bool CommandLogArguments::load_data(const String tokens[], const size_t token_count)
{
    Log.traceln("Loading argument(s) for: %s", tokens[0].c_str());
    m_arguments = "";
    for (auto i{1}; i < token_count; ++i)
    {
        m_arguments += tokens[i] + " ";
    }
    return true;
}

/**
 * @brief Acknowledge LogArguments command
 *
 * @return true successful
 * @return false error
 */

bool CommandLogArguments::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("LogArguments");
    return status;
}

/**
 * @brief Execute LogArguments command
 *
 * @return true successful
 * @return false error
 */

bool CommandLogArguments::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("LogArguments");
    Log.traceln("Logging command arguments: %s", m_arguments.c_str());
    return status;
}

/**
 * @brief Validate the arguments for BackgroundRSSI command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandBackgroundRSSI::validate_arguments(const String tokens[], const size_t token_count) const
{
    Log.traceln("Validating %d argument(s) for: %s", token_count - 1, tokens[0].c_str());
    if (token_count != 2)
    {
        return false;
    }
    if (!is_numeric(tokens[1]))
    {
        return false;
    }
    long seconds = tokens[1].toInt();
    if (seconds < minimum_background_rssi_interval || seconds > maximum_background_rssi_interval)
    {
        return false;
    }
    return true;
}

/**
 * @brief Load argument for BackgroundRSSI command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandBackgroundRSSI::load_data(const String tokens[], const size_t token_count)
{
    Log.traceln("Loading argument for: %s", tokens[0].c_str());
    m_seconds = tokens[1].toInt();
    return true;
}

/**
 * @brief Acknowledge BackgroundRSSI command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandBackgroundRSSI::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("BackgroundRSSI: %d seconds", m_seconds);
    return status;
}

/**
 * @brief Execute BackgroundRSSI command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandBackgroundRSSI::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("BackgroundRSSI");
    Log.traceln("Requesting background RSSI for %s seconds", m_seconds.c_str());
    Message message(Message::background_rssi, m_seconds);
    return message.send() && status;
}

/**
 * @brief Acknowledge CurrentRSSI command
 * 
 * @return true successful
 * @return false error
 * 
 */

bool CommandCurrentRSSI::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("CurrentRSSI");
    return status;
}

/**
 * @brief Execute CurrentRSSI command
 * 
 * @return true successful
 * @return false error
 * 
 */ 

bool CommandCurrentRSSI::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("CurrentRSSI");
    Log.traceln("Requesting current RSSI");
    Message message(Message::current_rssi, "");
    return message.send() && status;
}
/**
 * @brief Validate the arguments for ModifyCCA command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandModifyCCA::validate_arguments(const String tokens[], const size_t token_count) const
{
    Log.traceln("Validating %d argument(s) for: %s", token_count - 1, tokens[0].c_str());
    if (token_count != 2)
    {
        return false;
    }
    if (!is_numeric(tokens[1]))
    {
        return false;
    }
    return true;
}

/**
 * @brief Load argument for ModifyCCA command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandModifyCCA::load_data(const String tokens[], const size_t token_count)
{
    Log.traceln("Loading argument for: %s", tokens[0].c_str());
    m_threshold = tokens[1];
    return true;
}

/**
 * @brief Acknowledge ModifyCCA command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandModifyCCA::acknowledge_receipt() const
{
    auto status{Command::acknowledge_receipt()};
    Log.verboseln("ModifyCCA: %s seconds", m_threshold.c_str());
    return status;
}

/**
 * @brief Execute ModifyCCA command
 *
 * @return true successful
 * @return false error
 *
 */

bool CommandModifyCCA::execute() const
{
    auto status{Command::execute()};
    Log.verboseln("ModifyCCA");
    Log.traceln("Requesting CCA threshold %s", m_threshold.c_str());
    Message message(Message::modify_cca, m_threshold);
    return message.send() && status;
}