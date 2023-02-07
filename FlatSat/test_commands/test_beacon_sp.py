##
# @file test_beacon_sp.py
# @brief Unit test Avionics Board BeaconSp command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 21 August 2022

"""Unit test Avionics Board BeaconSp command"""

import helper
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test BeaconSp command
#


class TestBeaconSp:
    """Test BeaconSp command"""

    ## 60 second spacing
    #
    def test_beacon_sp_60(self):

        interval = 60
        log = helper.collect(f"BeaconSp {interval}")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)

    ## 120 second spacing
    #
    def test_beacon_sp_120(self):

        interval = 120
        log = helper.collect(f"BeaconSp {interval}")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)

    ## 90 second spacing
    #
    def test_beacon_sp_90(self):

        interval = 90
        log = helper.collect(f"BeaconSp {interval}")
        assert helper.not_signed(log)
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
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.collect_timeout()

    ## error: no parameter
    #
    def test_beacon_sp_no_param(self):

        log = helper.collect("BeaconSp")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: two parameters
    #
    def test_beacon_sp_two_param(self):

        log = helper.collect("BeaconSp 100 200")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameter
    #
    def test_beacon_sp_param_invalid(self):

        log = helper.collect("BeaconSp test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## 60 second spacing signed
    #
    def test_beacon_sp_60_signed(self):

        interval = 60
        log = helper.collect(helper.generate_signed(f"BeaconSp {interval}"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)

    ## 120 second spacing signed
    #
    def test_beacon_sp_120_signed(self):

        interval = 120
        log = helper.collect(helper.generate_signed(f"BeaconSp {interval}"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)

    ## 90 second spacing signed
    #
    def test_beacon_sp_90_signed(self):

        interval = 90
        log = helper.collect(helper.generate_signed(f"BeaconSp {interval}"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)

    ## no beacon signed
    #
    def test_beacon_sp_0_signed(self):

        interval = 0
        log = helper.collect(helper.generate_signed(f"BeaconSp {interval}"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.collect_timeout()

    ## error: no parameter signed
    #
    def test_beacon_sp_no_param_signed(self):

        log = helper.collect(helper.generate_signed("BeaconSp"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: two parameters signed
    #
    def test_beacon_sp_two_param_signed(self):

        log = helper.collect(helper.generate_signed("BeaconSp 100 200"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameter signed
    #
    def test_beacon_sp_param_invalid_signed(self):

        log = helper.collect(helper.generate_signed("BeaconSp test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
