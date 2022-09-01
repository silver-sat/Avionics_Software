##
# @file test_beacon_sp.py
# @brief Unit test Avionics Board BeaconSp command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 21 August 2022

"""Unit test Avionics Board BeaconSp command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test BeaconSp command
#


class TestBeaconSp:
    """Test BeaconSp command"""

    ## 10 second spacing
    #
    def test_beacon_sp_10(self):

        interval = 10
        log = helper.collect(f"BeaconSp {interval}")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)

    ## 20 second spacing
    #
    def test_beacon_sp_20(self):

        interval = 20
        log = helper.collect(f"BeaconSp {interval}")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)

    ## 15 second spacing
    #
    def test_beacon_sp_15(self):

        interval = 15
        log = helper.collect(f"BeaconSp {interval}")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)

    ## no beacon
    #
    def test_beacon_sp_0(self):

        interval = 0
        log = helper.collect(f"BeaconSp {interval}")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.collect_timeout()

    ## error: no parameter
    #
    def test_beacon_sp_no_param(self):

        log = helper.collect("BeaconSp")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: two parameters
    #
    def test_beacon_sp_two_param(self):

        log = helper.collect("BeaconSp 10 20")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameter
    #
    def test_beacon_sp_param_invalid(self):

        log = helper.collect("BeaconSp test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
