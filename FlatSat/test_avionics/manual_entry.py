##
# @file manual_entry.py
# @brief Import script to enable manual entry of commands
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 27 February 2022

"""Import script to enable manual entry of commands"""

import serial
import datetime
import time

COMMAND_PORT = "/dev/tty.usbserial-A10MHKWZ"
BAUDRATE = 115200
TIMEOUT = 5

FEND = b"\xC0"
REMOTE_FRAME = b"\xAA"

cp = serial.Serial(COMMAND_PORT, BAUDRATE, timeout=TIMEOUT)

def now():
    return datetime.datetime.now(datetime.timezone.utc).strftime("%Y %m %d %H %M %S")

def now1m():
    return (datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(seconds = 60)).strftime("%Y %m %d %H %M %S")

def issue(string):
    return (cp.write(FEND + REMOTE_FRAME + string.encode("utf-8") + FEND))