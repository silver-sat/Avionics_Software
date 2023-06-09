##
# @file test_payload_beacons.py
# @brief SilverSat Payload Board beacon testing
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 June 2023
#
# This test case assumes no payload activity has yet occured
# Payload timings must be set equal to the relevant Payload Board timings
#

"""Test Payload Board beacon characters"""

import utility
import time

## Payload timings from PayloadBoard.cpp in seconds
#
payload_startup_delay = 90.0
payload_shutdown_delay = 15.0
payload_maximum_cycle = 10.0 * 60.0


## Payload Board beacon testing
#
class TestPayloadBoardBeacon:
    """Test Payload Board beacons"""

    ## reset the simulator, set the beacon interval and real time clock
    def test_setup(self):
        utility.payload_control("n")
        utility.issue(f"BeaconSp 60")
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")
        utc_time = time.strftime("%Y %m %d %H %M %S", time.gmtime())
        utility.issue(f"SetClock {utc_time}")
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SRC")

    ## validate no activity beacon
    #
    def test_no_activity_beacon(self):
        message = utility.collect_message_wait()
        assert utility.payload_beacon(message, "E")

    ## validate beacons for communications intervals
    #
    def test_paycomms(self):
        # Paycomms
        controls = {1: "S", 3: "U", 5: "A", 7: "H", 9: "5", 11: "B"}
        for control in controls:
            utility.payload_control("n")
            if control > 9:
                utility.payload_control("t")
            else:
                utility.payload_control(str(control))
            utility.issue(f"PayComms")
            message = utility.collect_message()
            assert utility.acknowledged_message(message)
            message = utility.collect_message()
            assert utility.response_sent(message, "PYC")
            time.sleep(
                max(control * 60.0, payload_startup_delay + payload_shutdown_delay)
            )
            utility.clear_messages()  # discard intervening beacons
            message = utility.collect_message_wait()
            assert utility.payload_beacon(message, controls[control])

    ## validate beacons for photo intervals
    def test_pictimes(self):
        # PicTimes
        controls = {1: "N", 3: "T", 5: "I", 7: "D", 9: "R", 11: "F"}
        for control in controls:
            utility.payload_control("n")
            if control > 9:
                utility.payload_control("t")
            else:
                utility.payload_control(str(control))
            start_time = time.gmtime(time.time() + 5.0)
            start_time = time.strftime("%Y %m %d %H %M %S", start_time)
            utility.issue(f"PicTimes {start_time}")
            message = utility.collect_message()
            assert utility.acknowledged_message(message)
            message = utility.collect_message()
            assert utility.response_sent(message, "SPT")
            time.sleep(
                max(control * 60.0, payload_startup_delay + payload_shutdown_delay)
            )
            utility.clear_messages()  # discard intervening beacons
            message = utility.collect_message_wait()
            assert utility.payload_beacon(message, controls[control])

    ## validate beacons for overcurrent
    #
    def test_overcurrent(self):
        # Over current
        controls = {1: "L", 3: "M", 5: "V", 7: "G", 9: "K"}
        for control in controls:
            utility.payload_control("n")
            utility.payload_control("t")
            utility.issue(f"PayComms")
            message = utility.collect_message()
            assert utility.acknowledged_message(message)
            message = utility.collect_message()
            assert utility.response_sent(message, "PYC")
            time.sleep(
                max(control * 60.0, payload_startup_delay + payload_shutdown_delay)
            )
            utility.clear_messages()  # discard intervening beacons
            utility.payload_control("o")
            message = utility.collect_message_wait()
            assert utility.payload_beacon(message, controls[control])
