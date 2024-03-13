##
# @file common.py
# @brief FlatSat test Avionics Board common functions
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 9 October 2022

"""FlatSat test Avionics Board common functions"""

import serial
import datetime
import re
import secrets
import hashlib
import hmac
import time

## port for command input and output

COMMAND_PORT = '/dev/cu.usbmodem11103'

## serial transmission speed

BAUDRATE = 57600

## default timeout for readline

TIMEOUT = 5

## extended timeout for readline

EXTENDED_TIMEOUT = 120

## KISS special characters

FEND = b'\xC0'  # frame end
FESC = b'\xDB'  # frame escape
TFEND = b'\xDC'  # transposed frame end
TFESC = b'\xDD'  # transposed frame escape

## KISS commands

LOCAL_FRAME = b'\x00'
REMOTE_FRAME = b'\xAA'
BEACON = b'\x07'
DIGITALIO_RELEASE = b'\x08'
STATUS = b'\x09'
HALT = b'\x0a'
MODIFY_FREQ = b'\x0B'
MODIFY_MODE = b'\x0C'
ADJUST_FREQ = b'\x0D'
TRANSMIT_CARRIER = b'\x17'
BACKGROUND_RSSI = b'\x18'
CURRENT_RSSI = b'\x19'
SWEEP_TRANSMITTER = b'\x1A'
SWEEP_RECEIVER = b'\x1B'
QUERY_REGISTER = b'\x1C'
RADIO_PING = b'\x33'

## serial port for commands and responses

command_port = serial.Serial(COMMAND_PORT, BAUDRATE, timeout=TIMEOUT)

## maximum read length

read_length = 256

## acknowledgement and response patterns

acknowledgment_pattern = re.compile(rb'ACK$')
negative_acknowledgment_pattern = re.compile(rb'NACK$')
set_clock_pattern = re.compile(rb'RES SRC$')
beacon_sp_pattern = re.compile(rb'RES SBI$')
pic_times_pattern = re.compile(rb'RES SPT$')
clear_pic_times_pattern = re.compile(rb'RES CPT$')
unset_clock_pattern = re.compile(rb'RES URC$')
reportt_pattern = re.compile(
    rb'RES GRC 20\d\d-(0[1-9]|1[012])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-4]):([0-5]\d):([0-5]\d)$'
)
get_pic_times_pattern = re.compile(
    rb'RES GPT [0-5]( 20\d\d-(0[1-9]|1[012])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-4]):([0-5]\d):([0-5]\d)){0,5}$'
)
telemetry_pattern = re.compile(
    rb'(RES GTY AX -?\d+\.\d+)( AY -?\d+\.\d+)( AZ -?\d+\.\d+)( RX -?\d+\.\d+)( RY -?\d+\.\d+)( RZ -?\d+\.\d+)( T -?\d+\.\d+)$'
)
power_pattern = re.compile(
    rb'(RES GPW)( BBV \d+\.\d+)( BBC \d+\.\d+)( TS1 -*\d+\.\d+)( TS2 -*\d+\.\d+)( 5VC \d+\.\d+)( L5V \d+\.\d+)( H1S \d)( H2S \d)( H3S \d)$'
)
comms_pattern = re.compile(rb'RES GRS radio status$')
beacon_interval_pattern = re.compile(rb'(RES GBI )(\d+)$')
no_operation_pattern = re.compile(rb'RES NOP$')
test_packet_pattern = re.compile(rb'RES STP test packet$')
pay_comms_pattern = re.compile(rb'RES PYC$')
twee_slee_pattern = re.compile(rb'RES TSL$')
watchdog_pattern = re.compile(rb'RES WDG$')
modify_frequency_pattern = re.compile(rb'RES RMF \d{9}$')
modify_mode_pattern = re.compile(rb'RES RMM \d$')
adjust_frequency_pattern = re.compile(rb'RES RAF -*\d{6}$')
transmit_CW_pattern = re.compile(rb'RES RTC CW mode complete$')
background_RSSI_pattern = re.compile(rb'RES RBR \d{3}$')
current_RSSI_pattern = re.compile(rb'RES RCR \d{3}$')
sweep_transmitter_pattern = re.compile(rb'RES RST sweep done$')
sweep_receiver_pattern = re.compile(rb'RES RSR \d{3} \d{9} \d{3}$')
query_register_pattern = re.compile(rb'RES RQR \d{3}$')
error_pattern = re.compile(rb'ERR$')


## Issue command
#
# Commands must be framed with KISS encoding
#
def issue(command):
    command_port.write(FEND + REMOTE_FRAME + command.encode('utf-8') + FEND)


## Collect message response
#
# Commands generate one or more messages, captured individually
#
def collect_message():
    message = command_port.read_until(expected=FEND)
    message = message + command_port.read_until(expected=FEND)
    # trim FEND, command, and trailing FEND
    message = message[2:-1]
    print(f'Message: {message}')
    return message


## Collect message response with delay
#
#
def collect_message_wait():
    command_port.timeout = EXTENDED_TIMEOUT
    message = command_port.read_until(expected=FEND)
    message = message + command_port.read_until(expected=FEND)
    command_port.timeout = TIMEOUT
    print(f'Message: {message}')
    return message


## Clear messages
#
# Empty the input buffer
#
def clear_messages():
    command_port.reset_input_buffer()


## Verify message
#
def verify_message(message, pattern):
    return pattern.search(message)


## Generate signed command
#
# Sequence, salt, command and HMAC separated by pipe characters
# Command is blank delimited
# secret.txt must be identical to secret compiled into Avionics software
#
def generate_signed(command):
    secret = open('secret.txt', 'rb').read()
    salt = secrets.token_bytes(16)
    sequence = '1'.encode('utf-8')
    separator = '|'.encode('utf-8')
    command = command.encode('utf-8')
    command_hmac = hmac.new(secret, digestmod=hashlib.blake2s)
    command_hmac.update(sequence)
    command_hmac.update(separator)
    command_hmac.update(salt)
    command_hmac.update(separator)
    command_hmac.update(command)
    return (
        f'{sequence.decode(encoding="utf-8")}'
        f'{separator.decode(encoding="utf-8")}'
        f'{salt.hex()}'
        f'{separator.decode(encoding="utf-8")}'
        f'{command.decode(encoding="utf-8")}'
        f'{separator.decode(encoding="utf-8")}'
        f'{command_hmac.hexdigest()}'
    )


## Verify message timestamp sent
def message_timestamp_sent(message):
    return timestamp_pattern.search(message[2:-1].decode('utf-8'))


## Verify message pictimes sent
#
def message_pictimes_sent(message):
    return pictimes_pattern.search(message[2:-1].decode('utf-8'))


## Verify message telemetry sent
#
def message_telemetry_sent(message):
    return telemetry_pattern.search(message[2:-1].decode('utf-8'))


## Verify messaage power sent
#
def message_power_sent(message):
    return power_pattern.search(message[2:-1].decode('utf-8'))


## Verify message local GetComms sent
#
def message_local_status_request(message):
    return message.startswith(FEND + STATUS)


# todo: verify remote log and message sent


## Verify message beacon interval sent
#
def message_beacon_interval_sent(message):
    return beacon_interval_pattern.search(message[2:-1].decode('utf-8'))


## Verify message test packet sent
#
def message_test_packet_sent(message):
    return test_packet_pattern.search(message[2:-1].decode('utf-8'))


## Verify local recover antenna message sent
#
# Recover antenna will be sent if standard deployment fails
#
def local_recover_antenna(message):
    return message.startswith(FEND + DIGITALIO_RELEASE)


## Verify message local halt message sent
#
# Local halt message sent for TweeSlee command
#
def message_local_halt_message_sent(message):
    return message.startswith(FEND + HALT)


## Verify message local modify frequency message sent
#
# Local command for ModifyFrequency command
#
def message_local_modify_frequency_sent(message):
    return message.startswith(FEND + MODIFY_FREQ)


## Verify message remote modify frequency message sent
#
# Response for ModifyFrequency command
#
def message_remote_modify_frequency_sent(message):
    return modify_frequency_pattern.search(message[2:-1].decode('utf-8'))


## Verify message local modify mode message sent
#
# Local command for ModifyMode command
#
def message_local_modify_mode_sent(message):
    return message.startswith(FEND + MODIFY_MODE)


## Verify message remote modify mode message sent
#
# Local command for ModifyMode command
#
def message_remote_modify_mode_sent(message):
    return modify_mode_pattern.search(message[2:-1].decode('utf-8'))


## Verify message local adjust frequency message sent
#
# Local command for AdjustFrequency command
#
def message_local_adjust_frequency_sent(message):
    return message.startswith(FEND + ADJUST_FREQ)


## Verify message remote adjust frequency message sent
#
# Response for AdjustFrequency command
#
def message_remote_adjust_frequency_sent(message):
    return adjust_frequency_pattern.search(message[2:-1].decode('utf-8'))


## Verify message local transmit CW message sent
#
# Local command for TransmitCW command
#
def message_local_transmit_CW_sent(message):
    return message.startswith(FEND + TRANSMIT_CARRIER)


## Verify message remote transmit CW message sent
#
# Local command for TransmitCW command
#
def message_remote_transmit_CW_sent(message):
    return transmit_CW_pattern.search(message[2:-1].decode('utf-8'))


## Verify message local background RSSI message sent
#
# Local command for BackgroundRSSI command
#
def message_local_background_RSSI_sent(message):
    return message.startswith(FEND + BACKGROUND_RSSI)


## Verify message remote background RSSI message sent
#
# Local command for BackgroundRSSI command
#
def message_remote_background_RSSI_sent(message):
    return background_RSSI_pattern.search(message[2:-1].decode('utf-8'))


## Verify message local current RSSI message sent
#
# Local command for CurrentRSSI command
#
def message_local_current_RSSI_sent(message):
    return message.startswith(FEND + CURRENT_RSSI)


## Verify message remote current RSSI message sent
#
# Local command for CurrentRSSI command
#
def message_remote_current_RSSI_sent(message):
    return current_RSSI_pattern.search(message[2:-1].decode('utf-8'))


## Verify message local sweep transmitter message sent
#
# Local command for SweepTransmitter command
#
def message_local_sweep_transmitter_sent(message):
    return message.startswith(FEND + SWEEP_TRANSMITTER)


## Verify message remote sweep transmitter message sent
#
# Local command for SweepTransmitter command
#
def message_remote_sweep_transmitter_sent(message):
    return sweep_transmitter_pattern.search(message[2:-1].decode('utf-8'))


## Verify message local sweep receiver message sent
#
# Local command for SweepReceiver command
#
def message_local_sweep_receiver_sent(message):
    return message.startswith(FEND + SWEEP_RECEIVER)


## Verify message remote sweep receiver message sent
#
# Local command for SweepReceiver command
#
def message_remote_sweep_receiver_sent(message):
    return sweep_receiver_pattern.search(message[2:-1].decode('utf-8'))


## Verify message local query register message sent
#
# Local command for QueryRegister command
#
def message_local_query_register_sent(message):
    return message.startswith(FEND + QUERY_REGISTER)


## Verify message remote query register message sent
#
# Local command for QueryRegister command
#
def message_remote_query_register_sent(message):
    return query_register_pattern.search(message[2:-1].decode('utf-8'))


## Verify local query register message sent
#
# Local command for QueryRegister command
#
def local_query_register_message_sent(message):
    return message.startswith(FEND + QUERY_REGISTER)


def now():
    return datetime.datetime.now(datetime.timezone.utc).strftime('%Y %m %d %H %M %S')


def now1m():
    return (
        datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(seconds=60)
    ).strftime('%Y %m %d %H %M %S')


def read():
    return command_port.read_all()
