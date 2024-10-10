##
# @file common.py
# @brief FlatSat test Avionics Board common functions
# @author Lee A. Congdon (lee@silversat.org)
# @author Benjamin S. Cohen (ben@silversat.org)
# @version 1.0.0
# @date 9 October 2022

"""FlatSat test Avionics Board common functions"""

import serial
import datetime
import re
import secrets
import hashlib
import hmac

## port for command input and output

COMMAND_PORT = "/dev/tty.usbserial-A10MHKWZ"

## serial transmission speed

BAUDRATE = 19200

## default timeout for readline

TIMEOUT = 5

## extended timeout for readline

EXTENDED_TIMEOUT = 120

## KISS special characters

FEND = b"\xC0"  # frame end
FESC = b"\xDB"  # frame escape
TFEND = b"\xDC"  # transposed frame end
TFESC = b"\xDD"  # transposed frame escape

## KISS commands

LOCAL_FRAME = b"\x00"
REMOTE_FRAME = b"\xAA"
BEACON = b"\x07"
DIGITALIO_RELEASE = b"\x08"
STATUS = b"\x09"
HALT = b"\x0A"
MODIFY_MODE = b"\x0C"
TOGGLE_RADIO_5V = b"\x0F"

## serial port for commands and responses

command_port = serial.Serial(COMMAND_PORT, BAUDRATE, timeout=TIMEOUT)

## maximum read length

read_length = 256

## acknowledgement and response patterns

acknowledgment_pattern = re.compile(rb"^ACK \d+$")
negative_acknowledgment_pattern = re.compile(rb"^NACK \d+$")
no_response_pattern = re.compile(rb"")
invalid_command_pattern = re.compile(rb"^ERR INV$")
set_clock_pattern = re.compile(rb"^RES SRC$")
beacon_sp_pattern = re.compile(rb"^RES SBI$")
pic_times_pattern = re.compile(rb"^RES SPT$")
SSDV_times_pattern = re.compile(rb"^RES SST$")
clear_pic_times_pattern = re.compile(rb"^RES CPT$")
clear_SSDV_times_pattern = re.compile(rb"^RES CST$")
unset_clock_pattern = re.compile(rb"^RES URC$")
reportt_pattern = re.compile(
    rb"^RES GRC 20\d\d-(0[1-9]|1[012])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-4]):([0-5]\d):([0-5]\d)$"
)
get_pic_times_pattern = re.compile(
    rb"^RES GPT [0-5]( 20\d\d-(0[1-9]|1[012])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-4]):([0-5]\d):([0-5]\d)){0,5}$"
)
get_SSDV_times_pattern = re.compile(
    rb"^RES GST [0-5]( 20\d\d-(0[1-9]|1[012])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-4]):([0-5]\d):([0-5]\d)){0,5}$"
)
telemetry_pattern = re.compile(
    rb"(^RES GTY AX -?\d+\.\d+)( AY -?\d+\.\d+)( AZ -?\d+\.\d+)( RX -?\d+\.\d+)( RY -?\d+\.\d+)( RZ -?\d+\.\d+)( T -?\d+\.\d+)$"
)
power_pattern = re.compile(
    rb"(^RES GPW)( BBV \d+\.\d+)( BBC \d+\.\d+)( TS1 -*\d+\.\d+)( TS2 -*\d+\.\d+)( 5VC \d+\.\d+)( L5V \d+\.\d+)( H1S \d)( H2S \d)( H3S \d)$"
)
# todo: update radio status pattern
comms_pattern = re.compile(b"^RES GRS .*$")
beacon_interval_pattern = re.compile(rb"^RES GBI \d+$")
no_operation_pattern = re.compile(rb"^RES NOP$")
test_packet_pattern = re.compile(rb"^RES STP test packet$")
pay_comms_pattern = re.compile(rb"^RES PYC$")
twee_slee_pattern = re.compile(rb"^RES TSL$")
watchdog_pattern = re.compile(rb"^RES WDG$")
modify_mode_pattern = re.compile(rb"^RES RMM \d$")
error_pattern = re.compile(rb"^ERR$")

# Sequence counter for commands

command_count = 0

## Issue command
#
# Commands must be framed with KISS encoding
#
def issue(command):

    secret = open("secret.txt", "rb").read()
    salt = (secrets.token_bytes(8))
    global command_count
    command_count = command_count + 1
    sequence = str(command_count).zfill(8).encode("utf-8")
    command = command.encode("utf-8")
    computed_hmac = hmac.new(secret, digestmod=hashlib.blake2s)
    computed_hmac.update(salt)
    computed_hmac.update(sequence)
    computed_hmac.update(command)
    signature = computed_hmac.hexdigest().encode("utf-8") + salt.hex().encode("utf-8") + sequence
    command_port.write(FEND + REMOTE_FRAME + signature + command + FEND)


## Issue local command
#
# Local commands must be framed with KISS encoding
#
def local(command):
    command_port.write(FEND + LOCAL_FRAME + command.encode("utf-8") + FEND)


## Collect message response
#
# Commands generate one or more messages, captured individually
#
def collect_message():
    message = command_port.read_until(expected=FEND)
    message = message + command_port.read_until(expected=FEND)
    message = message[2:-1]
    print(f"Message: {message}")
    return message


## Collect message response with delay
#
# Some commands do not generate immediate responses
#
def collect_message_wait():
    command_port.timeout = EXTENDED_TIMEOUT
    message = command_port.read_until(expected=FEND)
    message = message + command_port.read_until(expected=FEND)
    command_port.timeout = TIMEOUT
    message = message[2:-1]
    print(f"Message: {message}")
    return message


## Read the command port
#
# Read all messages from the command port
#
def read():
    return command_port.read_all()


## Clear messages
#
# Empty the input buffer
#
def clear_messages():
    command_port.reset_input_buffer()


## Verify message
#
# Verify that the message matches the pattern
#
def verify_message(message, pattern):
    return pattern.search(message)


## Current time in UTC formatted for SetClock command
#
# The time is formatted as "YYYY MM DD HH MM SS"
#
def now():
    return datetime.datetime.now(datetime.timezone.utc).strftime("%Y %m %d %H %M %S")


## Current time one minute in the future UTC formatted for PicTimes command
#
# The time is formatted as "YYYY MM DD HH MM SS"
#
def now1m():
    return (
        datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(seconds=60)
    ).strftime("%Y %m %d %H %M %S")
