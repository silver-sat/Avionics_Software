#!/usr/bin/env python3
##
# @file test_kiss.py
# @brief Test KISS formatted commands
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 21 September 2022
#

"""Test KISS formatted commands"""

import serial

## port for command input
COMMAND_PORT = "/dev/ttyUSB0"
## serial transmission speed
BAUDRATE = 115200
## KISS frame end
FEND = b'\xC0'
## KISS frame escape
FESC = b'\xDB'
## KISS transposed frame end
TFEND = b'\xDC'
## KISS transposed frame escape
TFESC = b'\xDD'

command_port = serial.Serial(COMMAND_PORT, BAUDRATE)

def to_kiss(command):
    output = FEND
    output += b'x00'
    for entry in command:
        if entry == FEND:
            output += FESC
            output += TFEND
        else: 
            if entry == FESC:
                output += FESC
                output += TFESC
            else:
                output += bytes(entry)
    output += FEND

def main():
    command = "N".encode("utf-8")
# 
    command_port.write(FEND)
    command_port.write(b'\x00')
    command_port.write(b'N')
    command_port.write(b'o')
    command_port.write(b'O')
    command_port.write(b'p')
    command_port.write(b'e')
    command_port.write(b'r')
    command_port.write(b'a')
    command_port.write(b't')
    command_port.write(b'e')
    command_port.write(FEND)

if __name__ == "__main__":
    main()