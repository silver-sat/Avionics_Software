##
# @file payload_simulator.py
# @brief FlatSat simulate Payload Board interface
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 19 February 2023

"""FlatSat simulate Payload Board interface"""

import board
import digitalio
import usb_cdc
import time
import random

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

overcurrent_pin = digitalio.DigitalInOut(board.D9)
overcurrent_pin.direction = digitalio.Direction.OUTPUT

# serial console

serial = usb_cdc.console

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

# overcurrent

overcurrent = False

# activity times

startup_delay = 30.0
photo_time = 30.0
communications_time = 60.0
shutdown_delay = 10.0

# Avionics Board will turn off Payload Board at startup
# assume indeterminate state at simulator start

power_state = power_unknown
simulator_state = simulator_unknown
timer_end = 0
control_signal = ""

print("Starting Payload Board simulator")
print("Enter n for normal operation; 1, 3, 5, 7, or 9 for cycle time; t for timeout, o for overcurrent")

while True:

#
# Read console and process control signals
#

    while serial.in_waiting:
        raw = serial.read()
        control_signal = raw.decode("utf-8")
        if control_signal == "n" or control_signal == "N" :
            print("setting Normal operation")
            photo_time = 30.0
            communications_time = 60.0
            overcurrent = False
            break
        if control_signal == "1 ":
            print("setting 1 minute activity")
            photo_time = 1 * 60
            communications_time = 1 * 60
            break
        if control_signal == "3":
            print("setting 3 minute activity")
            photo_time = 3 * 60
            communications_time = 3 * 60
            break
        if control_signal == "5":
            print("setting 5 minute activity")
            photo_time = 5 * 60
            communications_time = 5 * 60
            break
        if control_signal == "7":
            print("setting 7 minute activity")
            photo_time = 7 * 60
            communications_time = 7 * 60
            break
        if control_signal == "9":
            print("setting 9 minute activity")
            photo_time = 9 * 60
            communications_time = 9 * 60
            break
        if control_signal == "t" or control_signal == "T":
            print("setting timeout activity")
            photo_time = 11 * 60
            communications_time = 11 * 60
            break
        if control_signal == "o" or control_signal == "O":
            print("setting overcurrent")
            overcurrent = True
            break
        print("invalid control signal")


    if (payload_on_a.value + payload_on_b.value + payload_on_c.value) < 2:
        if power_state != power_on:
            print("Power is on")
            power_state = power_on
            simulator_state = simulator_startup
            state_transition = True
            if overcurrent:
                overcurrent_pin.value = True
    else:
        if power_state != power_off:
            print("Power is off")
            power_state = power_off
            simulator_state = simulator_off
            overcurrent_pin = False

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
                timer_end = time.monotonic() + (photo_time * random_multiplier)
            else:
                print("Communications mode")
                timer_end = time.monotonic() + (
                    communications_time * random_multiplier
                )
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
