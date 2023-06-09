##
# @file antenna_simulator.py
# @brief FlatSat simulate antenna interface
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 1 April 2023
#
# Based on CirduitPython i2ctarget
#

import board
from i2ctarget import I2CTarget

regs = [0xaa] * 0x81 
index = 0

print("Starting antenna simulator")

while True:
    with I2CTarget(board.SCL, board.SDA, [0x33]) as device:
        while True:
            r = device.request()

            if not r:
                # Maybe do some housekeeping
                continue

            with r:  # Closes the transfer if necessary by sending a NACK or feeding dummy bytes
                if r.address == 0x33:
                    if not r.is_read:  # Main write which is Selected read
                        print("Main write")
                        b = r.read(1)
                        print(f"b: {b}")
                        if not b or b[0] >= 0x81:
                            print("Index out of range")
                            break
                        index = b[0]
                        b = r.read(1)
                        if b:
                            regs[index] = b[0]
                    elif r.is_restart:  # Combined transfer: This is the Main read message
                        print("Main restart")
                        n = r.write(bytes([regs[index]]))
                        print(f"Wrote {n} bytes")
                    else:
                        print("Main read")
                        n = r.write(bytes([regs[index]]))
                        print(f"Wrote {n} bytes")
            print("Exiting r")
    print("Exiting I2CTarget")
print("Exiting program")
