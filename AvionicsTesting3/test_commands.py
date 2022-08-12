#!/usr/bin/env python3

"""Unit test Avionics Board commands
   
Lee A. Congdon
lee@silversat.org
4 August 2022
"""

from collections import namedtuple
import serial

Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

port = serial.Serial(port="/dev/ttyACM0", baudrate=115200)

# Validate the commands


def execute_command(command_string, error_expected, failure_expected):

    # Send the command

    port.write((command_string + "\n").encode("ascii"))

    # Collect the response

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


def test_commands():

    # Skip setup output

    log_data = ""
    while "Process Loop Test initialization completed" not in log_data:
        log_data = port.readline().decode("utf-8").strip()

        print(log_data)

    # Test the commands

    # Format: command and parameters, error expected, failure expected

    commands = [
        ["BeaconSp 20", False, False],
        ["PayComms", False, False],
        ["PicTimes 2023 8 8 10 10 0", False, False],
        ["ReportT", False, False],
        ["NoOperate", False, False],
        ["SetClock 2022 8 6 10 10 0", False, False],
        ["TweeSlee", False, False],
        ["Watchdog", True, False],
        ["GetPicTimes", False, False],
        ["GetTelemetry", False, False],
        ["GetPower", False, False],
        ["GetPhotos", False, False],
        ["GetComms", False, False],
        ["GetBeaconInterval", False, False],
        ["SendTestPacket", False, False],
        ["Unknown", True, True],
        ["Invalid", True, True],
    ]

    for command_pair in commands:
        print(*command_pair)
        execute_command(*command_pair)


# Initialization if run as script

if __name__ == "__main__":
    test_commands()
