##
# @file test_get_beacon_interval.py
# @brief Unit test Avionics Board GetBeaconInterval command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 22 August 2022

"""Unit test Avionics Board GetBeaconInterval command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test GetBeaconInterval command
#


class TestGetBeaconInterval:
    """Test GetBeaconInterval command"""

    ## get beacon interval
    #
    def test_get_beacon_interval(self):

        log = helper.collect("GetBeaconInterval")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.integer_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter
    #
    def test_get_beacon_interval_param(self):
        log = helper.collect("GetBeaconInterval test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
