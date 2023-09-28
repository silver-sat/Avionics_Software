##
# @file payload_simulator.py
# @brief FlatSat simulate Payload Board interface
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.2.0
# @date 19 February 2023

"""FlatSat simulate Payload Board interface"""

import board
import digitalio
import usb_cdc
import time

# Convert digital i/o lines state to LOW/HIGH

LOW = False
HIGH = True


def pin_state(value):
    if value:
        return "HIGH"
    return "LOW"


# Photo is low, communications is high
states_a = digitalio.DigitalInOut(board.D0)
states_a.direction = digitalio.Direction.INPUT
states_a.pull = digitalio.Pull.UP
states_b = digitalio.DigitalInOut(board.D1)
states_b.direction = digitalio.Direction.INPUT
states_b.pull = digitalio.Pull.UP
states_c = digitalio.DigitalInOut(board.D2)
states_c.direction = digitalio.Direction.INPUT
states_c.pull = digitalio.Pull.UP

# Payload on is active low
payload_on_a = digitalio.DigitalInOut(board.D3)
payload_on_a.direction = digitalio.Direction.INPUT
payload_on_a.pull = digitalio.Pull.UP
payload_on_b = digitalio.DigitalInOut(board.D4)
payload_on_b.direction = digitalio.Direction.INPUT
payload_on_b.pull = digitalio.Pull.UP
payload_on_c = digitalio.DigitalInOut(board.D5)
payload_on_c.direction = digitalio.Direction.INPUT
payload_on_c.pull = digitalio.Pull.UP

# Shutdown is active high, indeterminate at startup
shutdown_a = digitalio.DigitalInOut(board.D6)
shutdown_a.direction = digitalio.Direction.OUTPUT
shutdown_b = digitalio.DigitalInOut(board.D7)
shutdown_b.direction = digitalio.Direction.OUTPUT
shutdown_c = digitalio.DigitalInOut(board.D8)
shutdown_c.direction = digitalio.Direction.OUTPUT

# Overcurrent is active low
overcurrent_pin = digitalio.DigitalInOut(board.D9)
overcurrent_pin.direction = digitalio.Direction.OUTPUT
overcurrent_pin.value = HIGH

# Serial console for display and control

serial = usb_cdc.console

# Power states

power_off = 0
power_on = 1
power_unknown = 2

# Simulator states

simulator_startup = 0
simulator_running = 1
simulator_shutdown_requested = 2
simulator_off = 3
simulator_unknown = 4

# Default activity times in seconds
# Must correspond to values in PayloadBoard.cpp

startup_delay = 90.0
photo_time = 30.0
communications_time = 60.0
shutdown_delay = 15.0
timeout_activity = 11.0 * 60.0

# Avionics Board will turn off Payload Board at startup

power_state = power_unknown
simulator_state = simulator_unknown
timer_end = 0.0
control_signal = ""
start_time = time.monotonic()
stop_time = 0.0

print("Starting Payload Board simulator")
print("Press n for normal operation")
print("Press a digit for specific cycle time in minutes")
print("Press t for timeout operation")
print("Press o for overcurrent")

while True:
    #  Read console and process control signals

    while serial.in_waiting:
        raw = serial.read()
        control_signal = raw.decode("utf-8")
        if control_signal == "n" or control_signal == "N":
            print("Setting normal operation")
            photo_time = 30.0
            communications_time = 60.0
            overcurrent_pin.value = HIGH  # Over current is active low
            break
        if control_signal in "123456789":
            interval = int(control_signal)
            print(f"Activity duration {interval} minute(s)")
            photo_time = int(control_signal) * 60.0
            communications_time = int(control_signal) * 60.0
            break
        if control_signal == "t" or control_signal == "T":
            print("Setting overtime activity duration")
            photo_time = timeout_activity
            communications_time = timeout_activity
            break
        if control_signal == "o" or control_signal == "O":
            print("Setting overcurrent signal")
            overcurrent_pin.value = LOW  # Over current is active low
            break
        print("Invalid control signal")

    # Check for power on transition

    on_a = payload_on_a.value
    on_b = payload_on_b.value
    on_c = payload_on_c.value
    if (on_a + on_b + on_c) < 2:
        if power_state != power_on:
            print(f"payload_on_a: {pin_state(on_a)}")
            print(f"payload_on_b: {pin_state(on_b)}")
            print(f"payload_on_c: {pin_state(on_c)}")
            start_time = time.monotonic()
            print(f"Power is on\n")
            power_state = power_on
            simulator_state = simulator_startup
            state_transition = True

    # Check for power off transistion

    else:
        if power_state != power_off:
            print(f"payload_on_a: {pin_state(on_a)}")
            print(f"payload_on_b: {pin_state(on_b)}")
            print(f"payload_on_c: {pin_state(on_c)}")
            stop_time = time.monotonic()
            print(f"Power is off, duration {stop_time - start_time}\n")
            power_state = power_off
            simulator_state = simulator_off

    # Check for simulator startup transition

    if simulator_state == simulator_startup:
        if state_transition:
            print("Initialization")
            timer_end = time.monotonic() + startup_delay
            state_transition = False
        if time.monotonic() >= timer_end:
            shutdown_a.value = LOW
            shutdown_b.value = LOW
            shutdown_c.value = LOW
            simulator_state = simulator_running
            state_transition = True

    if simulator_state == simulator_running:
        if state_transition:
            print("Running")
            if (states_a.value + states_b.value + states_c.value) < 2:
                print(f"states_a: {pin_state(states_a.value)}")
                print(f"states_b: {pin_state(states_b.value)}")
                print(f"states_c: {pin_state(states_c.value)}")
                print("Photo mode")
                timer_end = time.monotonic() + max(0, photo_time - startup_delay)
            else:
                print(f"states_a: {pin_state(states_a.value)}")
                print(f"states_b: {pin_state(states_b.value)}")
                print(f"states_c: {pin_state(states_c.value)}")
                print("Communications mode")
                timer_end = time.monotonic() + max(
                    0, communications_time - startup_delay
                )
            state_transition = False
        if time.monotonic() >= timer_end:
            simulator_state = simulator_shutdown_requested
            state_transition = True

    if simulator_state == simulator_shutdown_requested:
        if state_transition:
            print("Requesting shutdown")
            shutdown_a.value = HIGH
            shutdown_b.value = HIGH
            shutdown_c.value = HIGH
            timer_end = time.monotonic() + shutdown_delay
            state_transition = False
        if time.monotonic() >= timer_end:
            print("Shutdown complete")
            shutdown_a.value = LOW
            shutdown_b.value = LOW
            shutdown_c.value = LOW
            simulator_state = simulator_off
