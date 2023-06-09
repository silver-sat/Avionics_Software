##
# @file antenna_simulator.py
# @brief FlatSat simulate antenna interface
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 1 April 2023
#
# Based on CircuitPython i2ctarget
#

import board
from i2ctarget import I2CTarget

print("Starting antenna simulator")

with I2CTarget(board.SCL, board.SDA, [0x33]) as device:
    while True:
        r = device.request()
        if not r:
            continue
        with r:  # Closes the transfer if necessary by sending a NACK or feeding dummy bytes
            print("Request received")
            if not r.is_read:  # Main write which is Selected read
                print("Write to antenna")
                b = r.read(1)
                print(f"Value: {b}")
            else:
                print("Read from antenna")
                n = r.write(bytes([0xF5, 0x00, 0x50, 0xFF]))
                print(f"Wrote {n} bytes")
        print("Request complete")