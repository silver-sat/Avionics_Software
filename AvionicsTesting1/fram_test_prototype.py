#
# Test Adafruit FRAM breakout
# Lee A. Congdon
# 16 May 2022
#

import board
import busio
import adafruit_fram
import random

ZEROS_BYTE = int(0x00)
ONES_BYTE = int(0xFF)
ALTERNATING_BYTE = int(0xAA)

# Set up i2c connection

i2c = board.I2C()
fram = adafruit_fram.FRAM_I2C(i2c, address=0x50)

# Identify the test

print("Starting FRAM Test Suite")

# Get the size of the FRAM in bytes

print("Checking size of FRAM")

size = 0
progress_counter = 0
while True:

    try:
        fram[size] = 1
    except ValueError:
        print(f"\nSize in bytes is: {size}")
        break
    
    size += 1
    progress_counter += 1
    if progress_counter > 1000:
        print(".", end="")
        progress_counter = 0

if size == len(fram):
    print("Size agrees with reported length")
else:
    print(f"Error, size does not equal reported length")

# Write and read alternate zeros and ones ascending

print("Starting alternating ones and zeros test")

progress_counter = 0
for index in range(len(fram)):
    
    try:
        fram[index] = ALTERNATING_BYTE
        value = fram[index]
        if int(value[0]) != ALTERNATING_BYTE:
            raise RuntimeError

    except RuntimeError:
        print(f"I/O error at address: {index:#06x}")
    
    progress_counter += 1
    if progress_counter > 1000:
        print(".", end="")
        progress_counter = 0

print("\nAlternating ones and zeros test complete")

# Write and read zeros desecending

print("Starting zeros descending test")

progress_counter = 0
for index in range(len(fram) - 1, -1, -1):
    
    try:
        fram[index] = ZEROS_BYTE
        value = fram[index]
        if int(value[0]) != ZEROS_BYTE:
            raise RuntimeError

    except RuntimeError:
        print(f"I/O error at address: {index:#06x}")
    
    progress_counter += 1
    if progress_counter > 1000:
        print(".", end="")
        progress_counter = 0

print("\nZeros descending test complete")

# Write and read ones in random locations

print("Starting ones random test")

test_size = len(fram)
progress_counter = 0
for _ in range(test_size):
    location = random.randrange(0, len(fram))
    
    try:
        fram[location] = ONES_BYTE
        value = fram[location]
        if int(value[0]) != ONES_BYTE:
            raise RuntimeError

    except RuntimeError:
        print(f"I/O error at address: {location:#06x}")
    
    progress_counter += 1
    if progress_counter > 1000:
        print(".", end="")
        progress_counter = 0

print("\nOnes random test complete")

print("FRAM test suite complete")
