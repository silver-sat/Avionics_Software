##
# @file helper.py
# @brief Unit test Avionics Board helper functions
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 20 August 2022

"""Unit test Avionics Board helper functions"""

import serial
from collections import namedtuple
from datetime import timedelta

PORT = "/dev/ttyACM0"
BAUDRATE = 115200
TIMEOUT = 5
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Issue command and collect response
#
def collect(command):

    s = serial.Serial(PORT, BAUDRATE, timeout=TIMEOUT)
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

    s = serial.Serial(PORT, BAUDRATE, timeout=TIMEOUT)
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
def payload_power_off(log):

    return any([item.detail == "Payload power off" for item in log])


## Collect through two beacon tranmissions
#
def collect_two_beacons(interval):

    s = serial.Serial(PORT, BAUDRATE, timeout=interval + TIMEOUT)
    log = []
    log_data = s.readline().decode("utf-8").strip()
    log.append(Entry(*(log_data.split(maxsplit=2))))
    log_data = s.readline().decode("utf-8").strip()
    log.append(Entry(*(log_data.split(maxsplit=2))))
    s.close()
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
    return (timedelta1 - timedelta2 - timedelta(seconds=length)) < timedelta(seconds=0.5)


## Collect beacons with timeout
#
def collect_timeout(interval = 60):

    s = serial.Serial(PORT, BAUDRATE, timeout=interval)
    index = 0
    beacons_found = 0
    while index < 2:
        log_data = s.readline().decode("utf-8").strip()
        if "Transmitting beacon" in log_data:
            beacons_found += 1
        index += 1
    s.close()
    return beacons_found == 0
