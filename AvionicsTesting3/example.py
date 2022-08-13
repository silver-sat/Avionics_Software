#!/usr/bin/env python3
"""! @brief Sample python program to interact with Avionics Board"""
##
# @file example.py
# @brief Sample python program to interact with Avionics Board
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 4 August 2022

## Imports
from serial import serial

## Access serial port
port = serial.Serial(port="/dev/ttyACM0", baudrate=115200)

## Display setup output
while True:
    if port.in_waiting:
        output = str(port.readline(), "utf-8").strip()  # capture data from the port
        print(output)
        if "Process Loop Test initialization complete" in output:
            break

## Send a command
port.write(b"NoOperate\n")

## Display response and any other activity
while True:
    print(port.readline().decode("utf-8").strip())
