##
# @file helper.py
# @brief Unit test Avionics Board helper functions
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 20 August 2022

"""Unit test Avionics Board helper functions"""

import serial
from collections import namedtuple

PORT = "/dev/ttyACM0"
BAUDRATE = 115200
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Issue command and collect response
#
def collect(command):

    s = serial.Serial(PORT, BAUDRATE)
    s.write((command + "\n").encode("utf-8"))
    log = []
    log_data = ""
    while ("Command executed" not in log_data) & ("Command failed" not in log_data):
        log_data = s.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))
    s.close()
    return log


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

    return any([item.detail == "Command executed" for item in log])


## Collect through power off check
#
def collect_through_power_off(command):

    s = serial.Serial(PORT, BAUDRATE)
    s.write((command + "\n").encode("utf-8"))
    log = []
    log_data = ""
    while "Payload power off" not in log_data:
        log_data = s.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))
    s.close()
    return log


## Verify local stop message sent
#
def local_stop_message_sent(log):

    return any([item.detail == "Sending message: LOCSTOP" for item in log])

## Verify payload power off
#
# @param log formatted as an Entry
# @return true if power off entry
# @return false if no power off entry
#
def payload_power_off(log):

    return any([item.detail == "Payload power off" for item in log])
