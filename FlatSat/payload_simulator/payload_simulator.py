##
# @file payload_simulator.py
# @brief FlatSat simulate Payload Board interface
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 19 February 2023

"""FlatSat simulate Payload Board interface"""

import board
import digitalio
import time
import random

# power states

power_off = 0
power_on = 1
power_unknown = 2

# simulator states

simulator_startup = 0
simulator_running = 1
simulator_shutdown_requested = 2
simulator_off = 3
simulator_unknown = 4

# activity times

startup_delay = 30.0
mean_photo_time = 30.0
mean_communications_time = 60.0
shutdown_delay = 10.0

# digital i/o lines

states_a = digitalio.DigitalInOut(board.D0)
states_a.direction = digitalio.Direction.INPUT
states_a.pull = digitalio.Pull.UP
states_b = digitalio.DigitalInOut(board.D1)
states_b.direction = digitalio.Direction.INPUT
states_b.pull = digitalio.Pull.UP
states_c = digitalio.DigitalInOut(board.D2)
states_c.direction = digitalio.Direction.INPUT
states_c.pull = digitalio.Pull.UP

payload_on_a = digitalio.DigitalInOut(board.D3)
payload_on_a.direction = digitalio.Direction.INPUT
payload_on_a.pull = digitalio.Pull.UP
payload_on_b = digitalio.DigitalInOut(board.D4)
payload_on_b.direction = digitalio.Direction.INPUT
payload_on_b.pull = digitalio.Pull.UP
payload_on_c = digitalio.DigitalInOut(board.D5)
payload_on_c.direction = digitalio.Direction.INPUT
payload_on_c.pull = digitalio.Pull.UP

shutdown_a = digitalio.DigitalInOut(board.D6)
shutdown_a.direction = digitalio.Direction.OUTPUT
shutdown_b = digitalio.DigitalInOut(board.D7)
shutdown_b.direction = digitalio.Direction.OUTPUT
shutdown_c = digitalio.DigitalInOut(board.D8)
shutdown_c.direction = digitalio.Direction.OUTPUT

# Avionics Board will turn off Payload Board at startup
# assume indeterminate state at simulator start

power_state = power_unknown
simulator_state = simulator_unknown
timer_end = 0

print("Starting Payload Board simulator")

while True:
    
    if (payload_on_a.value + payload_on_b.value + payload_on_c.value) < 2:
         if power_state != power_on:
            print("Power is on")
            power_state = power_on
            simulator_state = simulator_startup
            state_transition = True
    else:
         if power_state != power_off:
            print("Power is off")
            power_state = power_off
            simulator_state = simulator_off

    if simulator_state == simulator_startup:
        if state_transition:
            print("Initialization")
            timer_end = time.monotonic() + startup_delay
            state_transition = False
        if time.monotonic() >= timer_end:
            shutdown_a.value = False
            shutdown_b.value = False
            shutdown_c.value = False
            simulator_state = simulator_running
            state_transition = True

    if simulator_state == simulator_running:
        if state_transition:
            print("Running")
            random_multiplier = random.randrange(8, 12) / 10.0
            if (states_a.value + states_b.value + states_c.value) < 2:
                print("Photo mode")
                timer_end = time.monotonic() + (mean_photo_time*random_multiplier)
            else:
                print("Communications mode")
                timer_end = time.monotonic() + (mean_communications_time * random_multiplier)
            state_transition = False
        if time.monotonic() >= timer_end:
            simulator_state = simulator_shutdown_requested
            state_transition = True

    if simulator_state == simulator_shutdown_requested:
        if state_transition:
            print("Requesting shutdown")
            shutdown_a.value = True
            shutdown_b.value = True
            shutdown_c.value = True
            timer_end = time.monotonic() + shutdown_delay
            state_transition = False
        if time.monotonic() >= timer_end:
            print("Shutdown complete")
            simulator_state = simulator_off

