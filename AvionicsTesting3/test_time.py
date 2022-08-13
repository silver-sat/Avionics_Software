#!/usr/bin/env python3
"""! @brief Unit test Avionics Board external realtime clock"""

##
# @file test_time.py   
# @brief Unit test Avionics Board realtime clock
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 5 August 2022

## Imports
from collections import namedtuple
import serial

## Field names for response
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Access serial port
port = serial.Serial(port="/dev/ttyACM0", baudrate=115200)

## Validate commands
#
# @param command_string command to be executed
# @param error_expected true if command will generate error
# @param failure_expected true if command will generate failure log entry
#

def execute_command(command_string, error_expected, failure_expected):

    # Send command

    port.write((command_string + "\n").encode("ascii"))

    # Collect response

    log = []
    log_data = ""
    while ("Command executed" not in log_data) & ("Command failed" not in log_data):
        log_data = port.readline().decode("utf-8").strip()
        log.append(Entry(*(log_data.split(maxsplit=2))))

    # Verify command acknowledged

    assert any([item.detail == "Command acknowledged" for item in log])

    # Verify no errors occurred

    if not error_expected:

        assert not any(
            [
                (item.level == "FATAL")
                | (item.level == "ERROR")
                | (item.level == "WARNING")
                for item in log
            ]
        )

    else:

        assert any(
            [
                (item.level == "FATAL")
                | (item.level == "ERROR")
                | (item.level == "WARNING")
                for item in log
            ]
        )

    # Verify command executed or failed

    if not failure_expected:
        assert any([item.detail == "Command executed" for item in log])

    else:
        assert any([item.detail == "Command failed" for item in log])

## Test time commands
#

def test_time():

    # Skip setup output

    log_data = ""
    while "Process Loop Test initialization completed" not in log_data:
        log_data = port.readline().decode("utf-8").strip()

        print(log_data)

    # Test the commands

    # Format: command and parameters, error expected, failure expected

    commands = [
        ["ReportT", False, False], 
        ["SetClock 2022 8 6 10 10 0", False, False],
        ["ReportT", False, False],
        ["Watchdog", True, False],
        ["ReportT", False, False],
        ["SetClock 2022 12 12 10 10 0", False, False],
        ["ReportT", False, False],
        ["SetClock -1 0 0 0 0 0", True, True],
        ["ReportT", False, False],
        ["UnsetClock", False, False],
        ["ReportT", True, True],
        ["PicTimes 2022 12 12 10 10 15", True, True],
        ["ReportT", True, True],
        ["SetClock 2022 12 12 10 10 0", False, False],
        ["SetClock 2022 12 12 10 10 0", False, False],
        ["ReportT", False, False],
        ["PicTimes 2022 10 10 10 10 0", True, True],

    ]

    for command_pair in commands:
        print(*command_pair)
        execute_command(*command_pair)


# Initialization if run as script

if __name__ == "__main__":
    test_time()
