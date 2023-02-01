##
# @file helper.py
# @brief FlatSat test Avionics Board helper functions
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 20 August 2022

"""FlatSat test Avionics Board helper functions"""

import serial
from datetime import timedelta
import re
import secrets
import hashlib
import hmac
import time

## port for command input and output
COMMAND_PORT = "/dev/tty.usbserial-A10MHKWZ"
## serial transmission speed
BAUDRATE = 115200
## default timeout for readline
TIMEOUT = 5
## KISS frame end
FEND = b"\xC0"
## KISS frame type
DATA_FRAME = b"\x00"
BEACON = b"\x07"
RECOVER_ANTENNA = b"\x08"
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
## serial port for commands and responses
command_port = serial.Serial(COMMAND_PORT, BAUDRATE, timeout=TIMEOUT)
## maximum read length
read_length = 256
## counter for sequencing commands
command_counter = 0


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


## Issue command and collect response
#
def collect(command):

    message = bytearray()
    with command_port as ser:
        ser.write(FEND + DATA_FRAME + command.encode("utf-8") + FEND)
        message = ser.read()
        message = message + ser.read_until(expected=FEND)
        print(message)
    return message


## Verify command acknowledged
#
def acknowledged(message):

    return bytes("ACK".encode("utf-8")) in message


## Verify command negative acknowledged
#
def negative_acknowledged(message):

    return "NACK" in message


## Verify command executed
#
def executed(message):

    return "RES" in message


## Verify beacon message sent
#


def local_beacon_message_sent(message):

    return message.startswith(FEND + BEACON)


## Verify local recover antenna message sent
#


def local_recover_antenna(message):

    return message.startwith(FEND + RECOVER_ANTENNA)


## Verify local status request message sent
#


def local_status_request(message):

    return message.startwith(FEND + STATUS)


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


## Verify local radio ping message sent
#
def local_radio_ping_message_sent(message):

    return message.startswith(FEND + RADIO_PING)
