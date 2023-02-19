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

mean_photo_time = 30
mean_communications_time = 60

# todo: verify direction of Pull
payload_on_a = DigitalInOut(board.D0)
payload_on_a.direction = Direction.INPUT
payload_on_a.pull = Pull.DOWN
payload_on_b = DigitalInOut(board.D1)
payload_on_b.direction = Direction.INPUT
payload_on_a.pull = Pull.DOWN
payload_on_c = DigitalInOut(board.D2)
payload_on_c.direction = Direction.INPUT
payload_on_a.pull = Pull.DOWN

# todo: verify direction of Pull
states_a = DigitalInOut(board.D3)
states_a.direction = Direction.INPUT
states_a.pull = Pull.DOWN
states_b = DigitalInOut(board.D4)
states_b.direction = Direction.INPUT
states_a.pull = Pull.DOWN
states_c = DigitalInOut(board.D5)
states_c.direction = Direction.INPUT
states_a.pull = Pull.DOWN

shutdown_a = DigitalInOut(board.D6)
shutdown_a.direction = Direction.OUTPUT
shutdown_b = DigitalInOut(board.D7)
shutdown_b.direction = Direction.OUTPUT
shutdown_c = DigitalInOut(board.D8)
shutdown_c.direction = Direction.OUTPUT


## Wait for two of payload_on_x to be HIGH
while():
    if (payload_on_a.value + payload_on_b.value + payload_on_c.value) > 2:
        print("Payload Board activated")
        random_multiplier = random.randrange(.8, 1.2)
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