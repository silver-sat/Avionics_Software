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
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.integer_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter
    #
    def test_get_beacon_interval_param(self):
        log = helper.collect("GetBeaconInterval test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## get beacon interval signed
    #
    def test_get_beacon_interval_signed(self):

        log = helper.collect(helper.generate_signed("GetBeaconInterval"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.integer_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter signed
    #
    def test_get_beacon_interval_param_signed(self):
        log = helper.collect(helper.generate_signed("GetBeaconInterval test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
