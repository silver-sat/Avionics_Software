##
# @file test_basic_payload_board.py
# @brief SilverSat Payload Board basic interface testing
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 26 February 2023

"""Test Basic Payload Board interface functions"""

import helper
import time

## Basic Payload Board testing
#

class TestPayloadBoardInterface:
    """Test basic Payload Board interface"""

    ## no beacon
    #
    def test_beacon_sp_0(self):

        helper.issue(f"BeaconSp 0")
        # check log
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SBI")

    ## set realtime clock with current time
    #
    def test_set_clock(self):

        utc_time = time.strftime("%Y %m %d %H %M %S", time.gmtime())
        helper.issue(f"SetClock {utc_time}")
        # check log
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SRC")

    ## set picture times
    #
    def test_pic_times(self):
        start_time = time.gmtime(time.time() + 30)
        start_time = time.strftime("%Y %m %d %H %M %S", start_time)
        # check logs
        log = helper.collect_through_power_off(f"PicTimes {start_time}")
        assert helper.not_signed(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.payload_power_off(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SPT")

    ## start payload communications
    #

    def test_pay_comms(self):
        # check logs
        log = helper.collect_through_power_off("PayComms")
        assert helper.not_signed(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.payload_power_off(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "PYC")
