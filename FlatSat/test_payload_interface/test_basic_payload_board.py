##
# @file test_basic_payload_board.py
# @brief SilverSat Payload Board basic interface testing
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 26 February 2023

"""Test Basic Payload Board interface functions"""

import helper
from collections import namedtuple
from datetime import datetime
from datetime import timezone
import time

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Basic Payload Board testing
#

class TestPayloadBoardInterface:
    """Test basic Payload Board interface"""

    
    ## no beacon
    #
    def test_beacon_sp_0(self):

        interval = 0
        log = helper.collect(f"BeaconSp {interval}")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## set realtime clock with current time
    #
    def test_set_clock(self):

        utc_time = datetime.now(timezone.utc)
        log = helper.collect("SetClock " + utc_time.strftime("%Y %m %d %H %M %S"))
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## set picture times
    #
    def test_pic_times(self):
        start_time = time.gmtime(time.time() + 60)
        start_time = time.strftime("%Y %m %d %H %M %S", start_time)
        log = helper.collect_through_power_off(f"PicTimes {start_time}")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.payload_power_off(log)

    ## start payload communications
    #
    def test_pay_comms(self):
        log = helper.collect_through_power_off("PayComms")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.payload_power_off(log)