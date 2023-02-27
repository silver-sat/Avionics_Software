##
# @file payload_emulator.py
# @brief FlatSat emulate Payload Board interface
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 19 February 2023

"""FlatSat emulate Payload Board interface"""

import board
from digitalio import DigitalInOut, Direction, Pull
import time
import random

mean_photo_time = 10
mean_communications_time = 10

states_a = DigitalInOut(board.D0)
states_a.direction = Direction.INPUT
states_a.pull = Pull.UP
states_b = DigitalInOut(board.D1)
states_b.direction = Direction.INPUT
states_b.pull = Pull.UP
states_c = DigitalInOut(board.D2)
states_c.direction = Direction.INPUT
states_c.pull = Pull.UP

payload_on_a = DigitalInOut(board.D3)
payload_on_a.direction = Direction.INPUT
payload_on_a.pull = Pull.UP
payload_on_b = DigitalInOut(board.D4)
payload_on_b.direction = Direction.INPUT
payload_on_b.pull = Pull.UP
payload_on_c = DigitalInOut(board.D5)
payload_on_c.direction = Direction.INPUT
payload_on_c.pull = Pull.UP

shutdown_a = DigitalInOut(board.D6)
shutdown_a.direction = Direction.OUTPUT
shutdown_a.value = False
shutdown_b = DigitalInOut(board.D7)
shutdown_b.direction = Direction.OUTPUT
shutdown_b.value = False
shutdown_c = DigitalInOut(board.D8)
shutdown_c.direction = Direction.OUTPUT
shutdown_c.value = False

print("Starting Payload Board emulator")

while(True):
    # print(f"payload_on_a: {payload_on_a.value}")
    # print(f"payload_on_b: {payload_on_b.value}")
    # print(f"payload_on_c: {payload_on_c.value}")
    # print(f"states_a: {states_a.value}")
    # print(f"states_b: {states_b.value}")
    # print(f"states_c: {states_c.value}")
    # time.sleep(1.0)
    if (payload_on_a.value + payload_on_b.value + payload_on_c.value) > 2:
        print("Payload Board activated")
        random_multiplier = random.randrange(8, 12) / 10.0
        if (states_a.value + states_b.value + states_c.value) > 2:
            print("Communications mode")
            time.sleep(mean_communications_time * random_multiplier)
        else:
            print("Photo mode")
            time.sleep(mean_photo_time * random_multiplier)
        print("Requesting shutdown")
        shutdown_a.value = True
        shutdown_b.value = True
        shutdown_c.value = True
        time.sleep(1.0)
    else:
        shutdown_a.value = False
        shutdown_b.value = False
        shutdown_c.value = False
        