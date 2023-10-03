##
# @file payload_simulator_test.py
# @brief FlatSat test Payload Board simulator
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 3 October 2023

"""FlatSat test Payload Board simulator"""

import board
import digitalio
import time

## Convert digital i/o lines state to LOW/HIGH

LOW = False
HIGH = True

def pin_state(value):
    if value:
        return "HIGH"
    return "LOW"

print("Payload simulator test initializing")

# Photo is low, communications is high
states_a = digitalio.DigitalInOut(board.D0)
states_a.direction = digitalio.Direction.OUTPUT
states_b = digitalio.DigitalInOut(board.D1)
states_b.direction = digitalio.Direction.OUTPUT
states_c = digitalio.DigitalInOut(board.D2)
states_c.direction = digitalio.Direction.OUTPUT

# Payload on is active low
payload_on_a = digitalio.DigitalInOut(board.D3)
payload_on_a.direction = digitalio.Direction.OUTPUT
payload_on_b = digitalio.DigitalInOut(board.D4)
payload_on_b.direction = digitalio.Direction.OUTPUT
payload_on_c = digitalio.DigitalInOut(board.D5)
payload_on_c.direction = digitalio.Direction.OUTPUT

# Shutdown is active high
shutdown_a = digitalio.DigitalInOut(board.D6)
shutdown_a.direction = digitalio.Direction.INPUT
shutdown_a.pull = digitalio.Pull.DOWN
shutdown_b = digitalio.DigitalInOut(board.D7)
shutdown_b.direction = digitalio.Direction.INPUT
shutdown_b.pull = digitalio.Pull.DOWN
shutdown_c = digitalio.DigitalInOut(board.D8)
shutdown_c.direction = digitalio.Direction.INPUT
shutdown_c.pull = digitalio.Pull.DOWN

# Overcurrent is active low
overcurrent_pin = digitalio.DigitalInOut(board.D9)
overcurrent_pin.direction = digitalio.Direction.INPUT
overcurrent_pin.pull = digitalio.Pull.UP

print("Payload simulator test initialization complete")

while True:

    print("Powering down payload simulator")

    payload_on_a.value = HIGH
    payload_on_b.value = HIGH
    payload_on_c.value = HIGH

    print("Delaying 10 seconds")

    time.sleep(10)

    print("Setting photo mode")

    states_a.value = LOW
    states_b.value = LOW
    states_c.value = LOW

    print("Powering up payload simulator")

    payload_on_a.value = LOW
    payload_on_b.value = LOW
    payload_on_b.value = LOW

    print("Waiting for simulator to initialize")
    time.sleep(30)

    print("Waiting for shutdown signal")

    while shutdown_a.value + shutdown_b.value + shutdown_c.value < 2:
        pass

    print("Shutdown signal received")

    print("Waiting for shutdown completion")
    time.sleep(30)

    print("Powering down payload simulator")

    payload_on_a.value = HIGH
    payload_on_b.value = HIGH
    payload_on_c.value = HIGH

    print("Delaying 10 seconds")

    time.sleep(10)

    print("Setting communications mode")

    states_a.value = HIGH
    states_b.value = HIGH
    states_c.value = HIGH

    print("Powering up payload simulator")

    payload_on_a.value = LOW
    payload_on_b.value = LOW
    payload_on_b.value = LOW

    print("Waiting for simulator to initialize")
    time.sleep(30)

    print("Waiting for shutdown signal")

    while shutdown_a.value + shutdown_b.value + shutdown_c.value < 2:
        pass

    print("Shutdown signal received")

    print("Waiting for shutdown completion")
    time.sleep(30)
