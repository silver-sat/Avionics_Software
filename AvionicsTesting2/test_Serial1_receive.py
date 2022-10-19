##
# @file test_Serial1_receive.py
# @brief Unit test Avionics Serial1 receive
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 19 October 2022

"""Unit test Avionics Board Serial1 receive"""

import serial
import time

## port for command input
COMMAND_PORT = "/dev/ttyUSB0"
## serial transmission speed
BAUDRATE = 115200
## default timeout for readline
TIMEOUT = 5
## serial port for commands and responses
command_port = serial.Serial(COMMAND_PORT, BAUDRATE, timeout=TIMEOUT)

while True:
    command_port.write("Testing Serial1 input\n".encode("utf-8"))
    time.sleep(1)
