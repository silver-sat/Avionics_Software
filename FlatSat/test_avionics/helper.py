##
# @file helper.py
# @brief FlatSat test Avionics Board helper functions
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 20 August 2022

"""FlatSat test Avionics Board helper functions"""

import serial
from collections import namedtuple
from datetime import timedelta
import re
import secrets
import hashlib
import hmac
import time

## port for log output
LOG_PORT = "/dev/tty.usbmodem11101"
## port for command input and output
COMMAND_PORT = "/dev/tty.usbserial-A10MHKWZ"
## serial transmission speed
BAUDRATE = 115200
## default timeout for readline
TIMEOUT = 5
## KISS frame end
FEND = b"\xC0"
## KISS frame type
LOCAL_FRAME = b"\x00"
REMOTE_FRAME = b"\xAA"
BEACON = b"\x07"
MANUAL_RELEASE = b"\x08"
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
## counter for sequencing commands
command_counter = 0

## Collect initialization
#
def collect_initialization():

    log = []
    log_data = ""
    while "Avionics Process initialization completed" not in log_data:
        log_data = log_port.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))
        print(log_data)
    return log


## Verify initialization complete
#
def initialization_complete(log):

    return any(
        [item.detail == "Avionics Process initialization completed" for item in log]
    )

## FENDs received
#
def fends_received(message):
    return(message == (FEND + FEND))

## Generate signed command
#
def generate_signed(command):
    secret = open("secret.txt", "rb").read()
    salt = secrets.token_bytes(16)
    # todo: implement sequence number testing
    global command_counter
    command_counter += 1
    sequence = repr(command_counter).encode("utf-8")
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

## Issue command
#
def issue(command):

    command_port.write(FEND + REMOTE_FRAME + command.encode("utf-8") + FEND)

## Issue command and collect response
#
def collect_log():

    log = []
    log_data = ""
    while ("Executed (" not in log_data) & ("Failed (" not in log_data):
        log_data = log_port.readline().decode("utf-8").strip()
        print(log_data)
        log.append(Entry(*(log_data.split(maxsplit=2))))
    return log

## Collect response
#
def collect_message():

    message = command_port.read()  # read first FEND
    message = message + command_port.read_until(expected=FEND)
    print(f"Message: {message}")
    return message


## Simulate response to local command
#
def respond(command):

    command_port.write(FEND + LOCAL_FRAME + command + FEND)


## Send FEND
#
def send_FEND(count=1):

    index = 0
    while index < count:
        command_port.write(FEND)
        index += 1


## Verify command acknowledged
#
def acknowledged_message(message):

    return bytes("ACK".encode("utf-8")) in message


## Verify command negative acknowledged
#
def negative_acknowledged_message(message):

    return bytes("NACK".encode("utf-8")) in message


## Verify response sent
#
def response_sent(message, type):

    return bytes(("RES" + type).encode("utf-8")) in message


## Verify beacon message sent
#
def local_beacon_message_sent(message):

    return message.startswith(FEND + BEACON)


## Verify local recover antenna message sent
#


def local_recover_antenna(message):

    return message.startswith(FEND + MANUAL_RELEASE)


## Verify local status request message sent
#


def local_status_request(message):

    return message.startswith(FEND + STATUS)


## Verify local halt message sent
#
def local_halt_message_sent(message):

    return message.startswith(FEND + HALT)


## Verify local modify frequency message sent
#
def local_modify_frequency_message_sent(message):

    return message.startswith(FEND + MODIFY_FREQ)


## Verify local modify mode message sent
#
def local_modify_mode_message_sent(message):

    return message.startswith(FEND + MODIFY_MODE)


## Verify local adjust frequency message sent
#
def local_adjust_frequency_message_sent(message):

    return message.startswith(FEND + ADJUST_FREQ)


## Verify local transmit carrier message sent
#
def local_transmit_carrier_message_sent(message):

    return message.startswith(FEND + TRANSMIT_CARRIER)


## Verify local background RSSI message sent
#
def local_background_rssi_message_sent(message):

    return message.startswith(FEND + BACKGROUND_RSSI)


## Verify local current RSSI message sent
#
def local_current_rssi_message_sent(message):

    return message.startswith(FEND + CURRENT_RSSI)


## Verify local sweep transmitter message sent
#
def local_sweep_transmitter_message_sent(message):

    return message.startswith(FEND + SWEEP_TRANSMITTER)


## Verify local sweep receiver message sent
#
def local_sweep_receiver_message_sent(message):

    return message.startswith(FEND + SWEEP_RECEIVER)


## Verify local query register message sent
#
def local_query_register_message_sent(message):

    return message.startswith(FEND + QUERY_REGISTER)

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


## Verify command acknowledged
#
def acknowledged_log(log):

    return any([item.detail == "Acknowledging command" for item in log])

## Verify command negative acknowledged
#
def negative_acknowledged_log(log):

    return any([item.detail == "Negative acknowledging command" for item in log])


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


## Collect through power off check
#
def collect_through_power_off(command, interval=60):

    command_port.write(FEND + REMOTE_FRAME + command.encode("utf-8") + FEND)
    log = []
    log_data = ""
    time.sleep(interval)
    while "Payload power off" not in log_data:
        log_data = log_port.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))
        print(log_data)
    return log


## Verify local stop message sent
#
def local_stop_message_sent(log):

    return any([item.detail == "Sending local command: halt" for item in log])


## Verify payload power off
#
def payload_power_off(log):

    return any([item.detail == "Payload power off" for item in log])


## Collect through two beacon tranmissions
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
    timedelta1 = timedelta(
        hours=int(hours1),
        minutes=int(minutes1),
        seconds=int(seconds1),
        milliseconds=int(milliseconds1),
    )
    timedelta2 = timedelta(
        hours=int(hours2),
        minutes=int(minutes2),
        seconds=int(seconds2),
        milliseconds=int(milliseconds2),
    )
    return (timedelta1 - timedelta2 - timedelta(seconds=length)) < timedelta(
        seconds=0.5
    )


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


## Verify timestamp sent
#
def timestamp_sent(log):
    pattern = re.compile(
        r"\sRESGRC20\d\d-(0[1-9]|1[012])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-4]):([0-5]\d):([0-5]\d)$"
    )
    return any([pattern.search(item.detail) for item in log])


## Verify pictimes sent
#
def pictimes_sent(log):
    pattern = re.compile(
        r"\sRESGPT[0-5](20\d\d-(0[1-9]|1[012])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-4]):([0-5]\d):([0-5]\d)){0,5}$"
    )
    return any([pattern.search(item.detail) for item in log])


## Verify zero pictimes sent
#
def pictimes_zero_sent(log):

    return any([item.detail.endswith("content: RESGPT0") for item in log])


## Collect through reset pin cleared
#
def collect_through_reset_pin_cleared(command, interval=60):

    command_port.write(FEND + REMOTE_FRAME + command.encode("utf-8") + FEND)
    log = []
    log_data = ""
    while "Reset pin changed state to 1" not in log_data:
        log_data = log_port.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))
    return log


## Verify reset pin set
#
def reset_pin_set(log):

    return any([item.detail == "Reset pin changed state to 0" for item in log])


## Verify reset pin cleared
#
def reset_pin_cleared(log):

    return any([item.detail == "Reset pin changed state to 1" for item in log])


## Verify telemetry sent
#
# Temperature truncated in match string
#
def telemetry_sent(log):
    pattern = re.compile(
        r"\s(RESGTYAX-?\d+\.\d+)(AY-?\d+\.\d+)(AZ-?\d+\.\d+)(RX-?\d+\.\d+)(RY-?\d+\.\d+)(RZ-?\d+\.\d+)(T-?\d+\.\d+)$"
    )
    return any([pattern.search(item.detail) for item in log])


## Verify power sent
#
# Checks partial response
#
def power_sent(log):
    pattern = re.compile(
        r"\s(RESGPW)(VP1\d+\.\d+)(CP1\d+\.\d+)(VP2\d+\.\d+)(CP2\d+\.\d+)(VP3\d+\.\d+)(CP3\d+\.\d+)"
    )
    return any([pattern.search(item.detail) for item in log])


## Verify integer sent get beacon spacing
#
def integer_sent_GBI(log):
    pattern = re.compile(r"\s(RESGBI)(\d+)$")
    return any([pattern.search(item.detail) for item in log])

## Verify integer sent get photo count
#
def integer_sent_GPC(log):
    pattern = re.compile(r"\s(RESGPC)(\d+)$")
    return any([pattern.search(item.detail) for item in log])


## Verify local GetComms message sent
#
def local_get_comms_sent(log):

    return any(
        [
            item.detail == "Requesting radio status"
            for item in log
        ]
    )


## Verify test packet sent
#
def test_packet_sent(log):

    return any([item.detail.endswith("content: RESSTPTEST") for item in log])


## Send FEND
#
def send_FEND(count=1):
    index = 0
    while index < count:
        command_port.write(FEND)
        index += 1

## Discard messages
#
def discard_messages():
    command_port.reset_input_buffer()

# todo: verify beacon power_sent

# todo: verify deploy antenna sent