#!/usr/bin/env python3

"""
    Sample python program to interact with Avionics Board
    Lee A. Congdon
    lee@silversat.org
    4 August 2022
"""

import serial

port = serial.Serial(port="/dev/ttyACM0", baudrate=115200)

# Display the setup output

while(True):
    if (port.in_waiting):
        output = str(port.readline(), 'utf-8').strip()
        print (output)
        if "Process Loop Test initialization complete" in output:
            break

# Send a command

port.write(b"NoOperate\n")

# Display the response and other activity

while(True):
    print(port.readline().decode('utf-8').strip())
