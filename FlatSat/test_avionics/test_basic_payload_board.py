##
# @file test_basic_payload_board.py
# @brief SilverSat Payload Board basic interface testing
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 26 February 2023

"""Test Basic Payload Board interface functions"""

import utility
import time

## Basic Payload Board testing
#
class TestPayloadBoardInterface:
    """Test basic Payload Board interface"""

    ## no beacon
    #
    def test_beacon_sp_0(self):

        utility.issue(f"BeaconSp 0")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")

    ## set realtime clock with current time
    #
    def test_set_clock(self):

        utc_time = time.strftime("%Y %m %d %H %M %S", time.gmtime())
        utility.issue(f"SetClock {utc_time}")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SRC")

    ## set picture times
    #
    def test_pic_times(self):

        start_time = time.gmtime(time.time() + 30)
        start_time = time.strftime("%Y %m %d %H %M %S", start_time)
        # check log
        log = utility.collect_through_power_off(f"PicTimes {start_time}")
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        assert utility.payload_power_off(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SPT")

    ## start payload communications
    #

    def test_pay_comms(self):
        
        # check log
        log = utility.collect_through_power_off("PayComms")
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        assert utility.payload_power_off(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "PYC")
