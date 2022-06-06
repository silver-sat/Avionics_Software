#
# Example test with mock interfaces
#
# Lee A. Congdon
# 6 June 2022
#

from time import time
from unittest.mock import Mock

class TestClass():
    use_count = 0
    def run_test():
        return

def main():

    start = time()
    print("Starting functional test")

    # Microcontroller self test

    microcontroller = TestClass()
    microcontroller.run_test = Mock(return_value = True)
    microcontroller.run_test(type='basic')
    microcontroller.run_test.assert_called()

    # FRAM test

    fram = TestClass()
    fram.run_test = Mock(return_value = True)
    fram.run_test(type='basic')
    fram.run_test.assert_called()

    # Accelerometer and gyroscope test

    mpu = TestClass()
    mpu.run_test = Mock(return_value = True)
    mpu.run_test(type='basic')
    mpu.run_test.assert_called()

    # I2C switch test

    i2c = TestClass()
    i2c.run_test = Mock(return_value = True)
    i2c.run_test(type='basic')
    i2c.run_test.assert_called()

    # Watchdog chip test

    watchdog = TestClass()
    watchdog.run_test = Mock(return_value = True)
    watchdog.run_test(type='basic')
    watchdog.run_test.assert_called()

    # Real time clock test

    rtc = TestClass()
    rtc.run_test = Mock(return_value = True)
    rtc.run_test(type='basic')
    rtc.run_test.assert_called()

    # Drain buffer test

    drain = TestClass()
    drain.run_test = Mock(return_value = True)
    drain.run_test(type='basic')
    drain.run_test.assert_called()

    # Serial test

    serial = TestClass()
    serial.run_test = Mock(return_value = True)
    serial.run_test(type='basic')
    serial.run_test.assert_called()

    # USB test

    usb = TestClass()
    usb.run_test = Mock(return_value = True)
    usb.run_test(type='basic')
    usb.run_test.assert_called()

    print("Ending functional test")
    print(f'Completed in {(time() - start):8.3f} seconds')

if __name__ == '__main__':
    main()
