##
# @file helper.py
# @brief Unit test Avionics Board helper functions
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 20 August 2022

"""Unit test Avionics Board helper functions"""

import serial
from collections import namedtuple
from datetime import timedelta
import re
import secrets
import hashlib
import hmac
import time
import random

## port for log output
LOG_PORT = "/dev/ttyACM0"
## port for command input
COMMAND_PORT = "/dev/ttyUSB0"
## serial transmission speed
BAUDRATE = 115200
## default timeout for readline
TIMEOUT = 5
## KISS frame end
FEND = b"\xC0"
## KISS frame type
KISS_TYPE = b"\x00"
## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

command_port = serial.Serial(COMMAND_PORT, BAUDRATE, timeout=TIMEOUT)
log_port = serial.Serial(LOG_PORT, BAUDRATE, timeout=TIMEOUT)
command_counter = 0

## Collect initialization
#
def collect_initialization():

    log = []
    log_data = ""
    while "Payload power off" not in log_data:
        log_data = log_port.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))
        print(log_data)
    return log


## Verify initialization complete
#
def initialization_complete(log):

    return any(
        [item.detail == "Process Loop Test initialization completed" for item in log]
    )


## Generate signed command
#
def generate_signed(command):
    secret = open("secret.txt", "rb").read()
    salt = secrets.token_bytes(16)
    # todo: implement sequence number testing
    global command_counter
    sequence = repr(command_counter).encode("utf-8")
    command_counter += 1
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

    command_port.write(FEND + KISS_TYPE + command.encode("utf-8") + FEND)
    log = []
    log_data = ""
    while ("Executed (" not in log_data) & ("Failed (" not in log_data):
        log_data = log_port.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))
    return log


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
def acknowledged(log):

    return any([item.detail == "Command acknowledged" for item in log])


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

    command_port.write(FEND + KISS_TYPE + command.encode("utf-8") + FEND)
    log = []
    log_data = ""
    time.sleep(interval)
    while "Payload power off" not in log_data:
        log_data = log_port.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))
    return log


## Verify local stop message sent
#
def local_stop_message_sent(log):

    return any([item.detail == "Sending message: LOCSTOP" for item in log])


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
        r"\sRES20\d\d-(0[1-9]|1[012])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-4]):([0-5]\d):([0-5]\d)$"
    )
    return any([pattern.search(item.detail) for item in log])


## Collect through reset pin cleared
#
def collect_through_reset_pin_cleared(command, interval=60):

    command_port.write(FEND + KISS_TYPE + command.encode("utf-8") + FEND)
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
        r"\s(RESAX-?\d+\.\d+)(AY-?\d+\.\d+)(AZ-?\d+\.\d+)(RX-?\d+\.\d+)(RY-?\d+\.\d+)(RZ-?\d+\.\d+)(T-?\d+\.\d+)$"
    )
    return any([pattern.search(item.detail) for item in log])


## Verify power sent
#
# Checks partial response
#
def power_sent(log):
    pattern = re.compile(
        r"\s(RES)(VP1\d+\.\d+)(CP1\d+\.\d+)(VP2\d+\.\d+)(CP2\d+\.\d+)(VP3\d+\.\d+)(CP3\d+\.\d+)"
    )
    return any([pattern.search(item.detail) for item in log])


## Verify integer sent
#
def integer_sent(log):
    pattern = re.compile(r"\s(RES)(\d+)$")
    return any([pattern.search(item.detail) for item in log])


## Verify local GetComms message sent
#
def local_get_comms_sent(log):

    return any([item.detail == "Sending message: LOCGetComms" for item in log])


## Verify test packet sent
#
def test_packet_sent(log):

    return any([item.detail == "Sending message: RESTEST" for item in log])
