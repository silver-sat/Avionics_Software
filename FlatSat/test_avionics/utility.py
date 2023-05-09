##
# @file utility.py
# @brief FlatSat test Avionics Board utility functions
# @author Lee A. Congdon (lee@silversat.org)
# @version 3.0.0
# @date 20 August 2022

"""FlatSat test Avionics Board utility functions"""

import serial
from collections import namedtuple
import datetime
import re
import secrets
import hashlib
import hmac
import time

## port for log output
LOG_PORT = "/dev/tty.usbmodem1301"
## port for command input and output
COMMAND_PORT = "/dev/tty.usbserial-A10MHKWZ"
## serial transmission speed
BAUDRATE = 115200
## default timeout for readline
TIMEOUT = 5
## extended timeout for readline
EXTENDED_TIMEOUT = 120
## KISS frame end
FEND = b"\xC0"
## KISS frame type
LOCAL_FRAME = b"\x00"
REMOTE_FRAME = b"\xAA"
BEACON = b"\x07"
DIGITALIO_RELEASE = b"\x08"
STATUS = b"\x09"
HALT = b"\x0a"
MODIFY_FREQ = b"\x0B"
MODIFY_MODE = b"\x0C"
ADJUST_FREQ = b"\x0D"
TRANSMIT_CARRIER = b"\x17"
BACKGROUND_RSSI = b"\x18"
CURRENT_RSSI = b"\x19"
SWEEP_TRANSMITTER = b"\x1A"
SWEEP_RECEIVER = b"\x1B"
QUERY_REGISTER = b"\x1C"
RADIO_PING = b"\x33"
## local command content
ACK = "ACK"
NACK = "NACK"
RES = "RES"
## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])
## serial port for commands and responses
command_port = serial.Serial(COMMAND_PORT, BAUDRATE, timeout=TIMEOUT)
## serial port for logging
log_port = serial.Serial(LOG_PORT, BAUDRATE, timeout=TIMEOUT)
## maximum read length
read_length = 256
## timestamp pattern
timestamp_pattern = re.compile(
    r"RESGRC 20\d\d-(0[1-9]|1[012])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-4]):([0-5]\d):([0-5]\d)$"
)
## pictimes pattern
pictimes_pattern = re.compile(
    r"RESGPT [0-5]( 20\d\d-(0[1-9]|1[012])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-4]):([0-5]\d):([0-5]\d)){0,5}$"
)
## telemetry pattern
telemetry_pattern = re.compile(
    r"(RESGTY AX -?\d+\.\d+)( AY -?\d+\.\d+)( AZ -?\d+\.\d+)( RX -?\d+\.\d+)( RY -?\d+\.\d+)( RZ -?\d+\.\d+)( T -?\d+\.\d+)$"
)
## power pattern
power_pattern = re.compile(
    r"(RESGPW)( BBV \d+\.\d+)( BBC \d+\.\d+)( TS1 -*\d+\.\d+)( TS2 -*\d+\.\d+)( 5VC \d+\.\d+)( H1S \d)( H2S \d)( H3S \d)$"
)
## beacon interval pattern
beacon_interval_pattern = re.compile(r"(RESGBI )(\d+)$")
## test packet pattern
test_packet_pattern = re.compile(r"RESSTP test packet$")
## modify frequency pattern
modify_frequency_pattern = re.compile(r"RESRMF \d{9}$")
## modify mode pattern
modify_mode_pattern = re.compile(r"RESRMM \d$")
## adjust frequency pattern
adjust_frequency_pattern = re.compile(r"RESRAF \d{9}$")
## transmit CW pattern
transmit_CW_pattern = re.compile(r"RESRTC \d{2}$")
## background RSSI pattern
background_RSSI_pattern = re.compile(r"RESRBR \d{2}$")
## current RSSI pattern
current_RSSI_pattern = re.compile(r"RESRCR \d{3}$")
## sweep transmitter pattern
sweep_transmitter_pattern = re.compile(r"RESRST sweep done$")
## sweep receiver pattern
sweep_receiver_pattern = re.compile(r"RESRSR \d{3} \d{9} \d{3}$")
## query register pattern
query_register_pattern = re.compile(r"RESRQR \d{3}$")

## Initialization services

## Collect initialization
#
def collect_initialization(interval=30):

    log = []
    log_data = ""
    log_port.timeout = interval
    while "Avionics Process initialization completed" not in log_data:
        log_data = log_port.readline().decode("utf-8").strip()
        print(log_data)
        log.append(Entry(*(log_data.split(maxsplit=2))))
    log_port.timeout = TIMEOUT
    return log


## Verify antenna deployed
#
def antenna_deployed(log):
    return any((item.detail == "All antenna doors open" for item in log))


## Verify initialization complete
#
def initialization_complete(log):

    return any(
        [item.detail == "Avionics Process initialization completed" for item in log]
    )


## FENDs received
#
def fends_received(message):
    return message == (FEND + FEND)


## Command services

## Issue command
#
# Commands must be framed with KISS encoding
#
def issue(command):

    command_port.write(FEND + REMOTE_FRAME + command.encode("utf-8") + FEND)


## Collect log response
#
# Command processing ends with an Executed or Failed log entry
#
def collect_log():
    log = []
    log_data = ""
    while ("Executed (" not in log_data) & ("Failed (" not in log_data):
        log_data = log_port.readline().decode("utf-8").strip()
        print(log_data)
        log.append(Entry(*(log_data.split(maxsplit=2))))
    return log


## Collect message response
#
# Commands generate one or more messages, captured individually
#
def collect_message():

    message = command_port.read_until(expected=FEND)
    message = message + command_port.read_until(expected=FEND)
    print(f"Message: {message}")
    return message


## Collect log radio response
#
def collect_log_radio_response():
    log = []
    log_data = ""
    while "Sending message:" not in log_data:
        log_data = log_port.readline().decode("utf-8").strip()
        print(log_data)
        log.append(Entry(*(log_data.split(maxsplit=2))))
    return log


## Verify command acknowledged
#
def acknowledged_log(log):

    return any([item.detail == "Acknowledging command" for item in log])


## Verify command negative acknowledged
#
def negative_acknowledged_log(log):

    return any([item.detail == "Negative acknowledging command" for item in log])


## Verify command acknowledged
#
# Each command is ACKed or NACKed in a message
#
def acknowledged_message(message):

    return bytes("ACK".encode("utf-8")) in message


## Verify command negative acknowledged
#
# Each command is ACKed or NACKed in a message
#
def negative_acknowledged_message(message):

    return bytes("NACK".encode("utf-8")) in message


## Collect local acknowledgement or negative acknowledgement
#
# Local ACKs and NACKs generate multiple log entries
#
def collect_ack_or_nack():

    log = []
    log_data = ""
    while ("Received ACK" not in log_data) & ("Received NACK" not in log_data):
        log_data = log_port.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))
    return log


## Verify response sent
#
# Each command receives a RESponse message
#
def response_sent(message, type):

    return bytes(("RES" + type).encode("utf-8")) in message


## Verify error response sent
#
# Some commands generate an error RESponse message
#
def error_response(message):

    return bytes(("RESERR").encode("utf-8")) in message


## Verify command not signed
#
def not_signed(log):

    return any([item.detail == "Command is not signed" for item in log])


## Verify command signed
#
def signed(log):

    return any([item.detail == "Command is signed" for item in log])


## Verify signature valid
#
def signature_valid(log):

    return any([item.detail == "Command signature valid" for item in log])


## Verify signature invalid
#
def signature_invalid(log):

    return any([item.detail == "Command signature invalid" for item in log])


## Verify no errors logged
#
def no_logged_errors(log):

    return not any(
        [
            (item.level == "FATAL")
            | (item.level == "ERROR")
            | (item.level == "WARNING")
            for item in log
        ]
    )


## Verify command executed
#
def executed(log):

    return any([item.detail.startswith("Executed (") for item in log])


## Get next sequence number
#
def get_next_sequence():
    issue("NoOperate")
    log = collect_log()
    for item in log:
        if "next sequence" in item.detail:
            sequence = item.detail
            sequence = sequence.removesuffix(")")
            sequence = sequence.rsplit(maxsplit=1)
            sequence = sequence[-1]
    collect_message()  # clear ACK from NoOperate
    collect_message()  # clear RES from NoOperate
    return sequence


## Generate signed command
#
# Sequence, salt, command and HMAC separated by pipe characters
# Command is blank delimited
# secret.txt must be identical to secret compiled into Avionics software
#
def generate_signed(command):
    secret = open("secret.txt", "rb").read()
    salt = secrets.token_bytes(16)
    sequence = get_next_sequence().encode("utf-8")
    separator = "|".encode("utf-8")
    command = command.encode("utf-8")
    command_hmac = hmac.new(secret, digestmod=hashlib.blake2s)
    command_hmac.update(sequence)
    command_hmac.update(separator)
    command_hmac.update(salt)
    command_hmac.update(separator)
    command_hmac.update(command)
    return (
        f"{sequence.decode(encoding='utf-8')}"
        f"{separator.decode(encoding='utf-8')}"
        f"{salt.hex()}"
        f"{separator.decode(encoding='utf-8')}"
        f"{command.decode(encoding='utf-8')}"
        f"{separator.decode(encoding='utf-8')}"
        f"{command_hmac.hexdigest()}"
    )


## Change satellite state services

## Verify beacon message sent
#
# Beacons are sent periodically at the beacon interval
#
def local_beacon_message_sent(message):

    return message.startswith(FEND + BEACON)


## Collect through two beacon tranmissions
#
# Assumes beacon spacing is less than interval
#
def collect_two_beacons(interval):

    log = []
    time.sleep(interval)
    log_data = log_port.readline().decode("utf-8").strip()
    log.append(Entry(*(log_data.split(maxsplit=2))))
    time.sleep(interval)
    log_data = log_port.readline().decode("utf-8").strip()
    log.append(Entry(*(log_data.split(maxsplit=2))))
    return log


## Verify beacon interval
#
def beacon_interval(length, log):

    hours1, minutes1, seconds1 = log[-1].timestamp.split(":")
    seconds1, milliseconds1 = seconds1.split(".")
    hours2, minutes2, seconds2 = log[-2].timestamp.split(":")
    seconds2, milliseconds2 = seconds2.split(".")
    timedelta1 = datetime.timedelta(
        hours=int(hours1),
        minutes=int(minutes1),
        seconds=int(seconds1),
        milliseconds=int(milliseconds1),
    )
    timedelta2 = datetime.timedelta(
        hours=int(hours2),
        minutes=int(minutes2),
        seconds=int(seconds2),
        milliseconds=int(milliseconds2),
    )
    return (
        timedelta1 - timedelta2 - datetime.timedelta(seconds=length)
    ) < datetime.timedelta(seconds=0.5)


## Collect beacons with timeout
#
def collect_timeout(interval=60):

    index = 0
    beacons_found = 0
    while index < 2:
        log_data = log_port.readline().decode("utf-8").strip()
        if "Transmitting beacon" in log_data:
            beacons_found += 1
        index += 1
    return beacons_found == 0


## Payload services

## Collect through power off check
#
# Assumes Payload Board is active for less than "interval" seconds
#
def collect_through_power_off(interval=120):

    log = []
    log_data = ""
    log_port.timeout = interval
    no_power_off = True
    while no_power_off:
        log_data = log_port.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))
        print(log_data)
        if "Payload power off" in log_data:
            no_power_off = False
    log_port.timeout = TIMEOUT
    return log


## Verify payload power off
#
def payload_power_off(log):

    return any([item.detail == "Payload power off" for item in log])


## Get satellite state services

## Verify log timestamp sent
#
def log_timestamp_sent(log):
    return any([timestamp_pattern.search(item.detail) for item in log])


## Verify message timestamp sent
def message_timestamp_sent(message):
    return timestamp_pattern.search(message[2:-1].decode("utf-8"))


## Verify log pictimes sent
#
def log_pictimes_sent(log):
    return any([pictimes_pattern.search(item.detail) for item in log])


## Verify message pictimes sent
#
def message_pictimes_sent(message):
    return pictimes_pattern.search(message[2:-1].decode("utf-8"))


## Verify zero pictimes sent
#
def pictimes_zero_sent(log):

    return any([item.detail.endswith("content: RESGPT 0") for item in log])


## Verify log telemetry sent
#
def log_telemetry_sent(log):
    return any([telemetry_pattern.search(item.detail) for item in log])


## Verify message telemetry sent
#
def message_telemetry_sent(message):
    return telemetry_pattern.search(message[2:-1].decode("utf-8"))


## Verify log power sent
#
def log_power_sent(log):
    return any([power_pattern.search(item.detail) for item in log])


## Verify messaage power sent
#
def message_power_sent(message):
    return power_pattern.search(message[2:-1].decode("utf-8"))


## Verify log local GetComms sent
#
def log_local_status_request(log):

    return any([item.detail == "Requesting radio status" for item in log])


## Verify message local GetComms sent
#
def message_local_status_request(message):

    return message.startswith(FEND + STATUS)


# todo: verify remote log and message sent

## Verify log beacon interval sent
#
def log_beacon_interval_sent(log):
    return any([beacon_interval_pattern.search(item.detail) for item in log])


## Verify message beacon interval sent
#
def message_beacon_interval_sent(message):
    return beacon_interval_pattern.search(message[2:-1].decode("utf-8"))


## Verify time sent
#
def time_sent(log):

    return any([item.detail.contains("RESGRC") for item in log])


## Invoke satellite operation services


## Verify log test packet sent
#
def log_test_packet_sent(log):
    return any([test_packet_pattern.search(item.detail) for item in log])


## Verify message test packet sent
#
def message_test_packet_sent(message):
    return test_packet_pattern.search(message[2:-1].decode("utf-8"))


## Invalid and unknown command services


## Verify buffer overflow
#
def buffer_overflow(log):

    return any([("Buffer overflow" in item.detail) for item in log])


## Radio command services

## Verify local recover antenna message sent
#
# Recover antenna will be sent if standard deployment fails
#
def local_recover_antenna(message):

    return message.startswith(FEND + DIGITALIO_RELEASE)


## Verify log local halt message sent
#
# Local halt message sent for TweeSlee command
#
def log_local_halt_message_sent(log):
    return any([item.detail == "Sending local command: halt" for item in log])


## Verify message local halt message sent
#
# Local halt message sent for TweeSlee command
#
def message_local_halt_message_sent(message):
    return message.startswith(FEND + HALT)


## Verify log local modify frequency message sent
#
# Local command for ModifyFrequency command
#
def log_local_modify_frequency_sent(log):
    return any([item.detail == "Requesting frequency modification" for item in log])


## Verify message local modify frequency message sent
#
# Local command for ModifyFrequency command
#
def message_local_modify_frequency_sent(message):
    return message.startswith(FEND + MODIFY_FREQ)


## Verify log remote modify frequency message sent
#
# Response for ModifyFrequency command
#
def log_remote_modify_frequency_sent(log):
    return any([modify_frequency_pattern.search(item.detail) for item in log])


## Verify message remote modify frequency message sent
#
# Response for ModifyFrequency command
#
def message_remote_modify_frequency_sent(message):
    return modify_frequency_pattern.search(message[2:-1].decode("utf-8"))


## Verify log local modify mode message sent
#
# Local command for ModifyMode command
#
def log_local_modify_mode_sent(log):
    return any([item.detail == "Requesting mode modification" for item in log])


## Verify message local modify mode message sent
#
# Local command for ModifyMode command
#
def message_local_modify_mode_sent(message):
    return message.startswith(FEND + MODIFY_MODE)


## Verify log remote modify mode message sent
#
# Local command for ModifyMode command
#
def log_remote_modify_mode_sent(log):
    return any([modify_mode_pattern.search(item.detail) for item in log])


## Verify message remote modify mode message sent
#
# Local command for ModifyMode command
#
def message_remote_modify_mode_sent(message):
    return modify_mode_pattern.search(message[2:-1].decode("utf-8"))


## Verify log local adjust frequency message sent
#
# Local command for AdjustFrequency command
#
def log_local_adjust_frequency_sent(log):
    return any([item.detail == "Requesting frequency adjustment" for item in log])


## Verify message local adjust frequency message sent
#
# Local command for AdjustFrequency command
#
def message_local_adjust_frequency_sent(message):
    return message.startswith(FEND + ADJUST_FREQ)


## Verify log remote adjust frequency message sent
#
# Response for AdjustFrequency command
#
def log_remote_adjust_frequency_sent(log):
    return any([adjust_frequency_pattern.search(item.detail) for item in log])


## Verify message remote adjust frequency message sent
#
# Response for AdjustFrequency command
#
def message_remote_adjust_frequency_sent(message):
    return adjust_frequency_pattern.search(message[2:-1].decode("utf-8"))


## Verify log local transmit CW message sent
#
# Local command for TransmitCW command
#
def log_local_transmit_CW_sent(log):
    return any([item.detail == "Requesting carrier wave" for item in log])


## Verify message local transmit CW message sent
#
# Local command for TransmitCW command
#
def message_local_transmit_CW_sent(message):
    return message.startswith(FEND + TRANSMIT_CARRIER)


## Verify log remote transmit CW message sent
#
# Local command for TransmitCW command
#
def log_remote_transmit_CW_sent(log):
    return any([transmit_CW_pattern.search(item.detail) for item in log])


## Verify message remote transmit CW message sent
#
# Local command for TransmitCW command
#
def message_remote_transmit_CW_sent(message):
    return transmit_CW_pattern.search(message[2:-1].decode("utf-8"))


## Verify log local background RSSI message sent
#
# Local command for BackgroundRSSI command
#
def log_local_background_RSSI_sent(log):
    return any([item.detail == "Requesting background RSSI" for item in log])


## Verify message local background RSSI message sent
#
# Local command for BackgroundRSSI command
#
def message_local_background_RSSI_sent(message):
    return message.startswith(FEND + BACKGROUND_RSSI)


## Verify log remote background RSSI message sent
#
# Local command for BackgroundRSSI command
#
def log_remote_background_RSSI_sent(log):
    return any([background_RSSI_pattern.search(item.detail) for item in log])


## Verify message remote background RSSI message sent
#
# Local command for BackgroundRSSI command
#
def message_remote_background_RSSI_sent(message):
    return background_RSSI_pattern.search(message[2:-1].decode("utf-8"))


## Verify log local current RSSI message sent
#
# Local command for CurrentRSSI command
#
def log_local_current_RSSI_sent(log):
    return any([item.detail == "Requesting current RSSI" for item in log])


## Verify message local current RSSI message sent
#
# Local command for CurrentRSSI command
#
def message_local_current_RSSI_sent(message):
    return message.startswith(FEND + CURRENT_RSSI)


## Verify log remote current RSSI message sent
#
# Local command for CurrentRSSI command
#
def log_remote_current_RSSI_sent(log):
    return any([current_RSSI_pattern.search(item.detail) for item in log])


## Verify message remote current RSSI message sent
#
# Local command for CurrentRSSI command
#
def message_remote_current_RSSI_sent(message):
    return current_RSSI_pattern.search(message[2:-1].decode("utf-8"))


## Verify log local sweep transmitter message sent
#
# Local command for SweepTransmitter command
#
def log_local_sweep_transmitter_sent(log):
    return any([item.detail == "Requesting transmitter sweep" for item in log])


## Verify message local sweep transmitter message sent
#
# Local command for SweepTransmitter command
#
def message_local_sweep_transmitter_sent(message):
    return message.startswith(FEND + SWEEP_TRANSMITTER)


## Verify log remote sweep transmitter message sent
#
# Local command for SweepTransmitter command
#
def log_remote_sweep_transmitter_sent(log):
    return any([sweep_transmitter_pattern.search(item.detail) for item in log])


## Verify message remote sweep transmitter message sent
#
# Local command for SweepTransmitter command
#
def message_remote_sweep_transmitter_sent(message):
    return sweep_transmitter_pattern.search(message[2:-1].decode("utf-8"))


## Verify log local sweep receiver message sent
#
# Local command for SweepReceiver command
#
def log_local_sweep_receiver_sent(log):
    return any([item.detail == "Requesting receiver sweep" for item in log])


## Verify message local sweep receiver message sent
#
# Local command for SweepReceiver command
#
def message_local_sweep_receiver_sent(message):
    return message.startswith(FEND + SWEEP_RECEIVER)


## Verify log remote sweep receiver message sent
#
# Local command for SweepReceiver command
#
def log_remote_sweep_receiver_sent(log):
    return any([sweep_receiver_pattern.search(item.detail) for item in log])


## Verify message remote sweep receiver message sent
#
# Local command for SweepReceiver command
#
def message_remote_sweep_receiver_sent(message):
    return sweep_receiver_pattern.search(message[2:-1].decode("utf-8"))


## Verify log local query register message sent
#
# Local command for QueryRegister command
#
def log_local_query_register_sent(log):
    return any([item.detail == "Requesting radio register" for item in log])


## Verify message local query register message sent
#
# Local command for QueryRegister command
#
def message_local_query_register_sent(message):
    return message.startswith(FEND + QUERY_REGISTER)


## Verify log remote query register message sent
#
# Local command for QueryRegister command
#
def log_remote_query_register_sent(log):
    return any([query_register_pattern.search(item.detail) for item in log])


## Verify message remote query register message sent
#
# Local command for QueryRegister command
#
def message_remote_query_register_sent(message):
    return query_register_pattern.search(message[2:-1].decode("utf-8"))


## Verify local query register message sent
#
# Local command for QueryRegister command
#
def local_query_register_message_sent(message):

    return message.startswith(FEND + QUERY_REGISTER)


## Verify local message received
#
def local_message_received(log):
    return any((item.detail.startswith("Local message received:") for item in log))


## Verify ACK or NACK ignored
#
# todo: handle NACK
#
def ack_or_nack_ignored(log):
    return any("Received ACK, ignored" in item.detail for item in log)


## Manual entry aids
#


def now():
    return datetime.datetime.now(datetime.timezone.utc).strftime("%Y %m %d %H %M %S")


def now1m():
    return (
        datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(seconds=60)
    ).strftime("%Y %m %d %H %M %S")


def issue(string):
    return command_port.write(FEND + REMOTE_FRAME + string.encode("utf-8") + FEND)


def read():
    return command_port.read_all()


## Exercise avionics board


def exercise_avionics():
    issue(f"SetClock {now()}")
    log = collect_log()
    message = collect_message()
    message = collect_message()
    issue("BeaconSp 60")
    log = collect_log()
    message = collect_message()
    message = collect_message()

    while True:
        time.sleep(5)
        issue("GetComms")
        log = collect_log()
        message = collect_message()
        message = collect_message()
        message = collect_message()
        time.sleep(5)
        issue(f"PicTimes {now1m()}")
        log = collect_log()
        message = collect_message()
        message = collect_message()
        time.sleep(5)
        issue(f"GetPower")
        log = collect_log()
        message = collect_message()
        message = collect_message()
        time.sleep(5)
        issue(f"GetTelemetry")
        log = collect_log()
        message = collect_message()
        message = collect_message()


## Radio simulator services

## Simulate response to local command
#
# Simulate Radio Board KISS-encoded local frame response to local command
#
def respond(command):

    command_port.write(FEND + LOCAL_FRAME + command + FEND)


## Send FEND
#
# Transmit a FEND on the command port
#
def send_FEND(count=1):

    index = 0
    while index < count:
        command_port.write(FEND)
        index += 1
