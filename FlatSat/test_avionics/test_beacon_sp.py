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
        helper.issue(f"BeaconSp {interval}")
        # check logs
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
        # verify beacon interval
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)
        # discard messages
        helper.discard_messages()

    ## 120 second spacing
    #
    def test_beacon_sp_120(self):

        interval = 120
        helper.issue(f"BeaconSp {interval}")
        # check logs
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
        # verify beacon interval
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)
        # discard messages
        helper.discard_messages()

    ## 90 second spacing
    #
    def test_beacon_sp_90(self):

        interval = 90
        helper.issue(f"BeaconSp {interval}")
        # check logs
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
        # verify beacon interval
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)
        # discard messages
        helper.discard_messages()

    ## no beacon
    #
    def test_beacon_sp_0(self):

        interval = 0
        helper.issue(f"BeaconSp {interval}")
        # check logs
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
        # verify beacon interval
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)
        # discard messages
        helper.discard_messages()

    ## error: no parameter
    #
    def test_beacon_sp_no_param(self):

        helper.issue(f"BeaconSp")
        # check logs
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.negative_acknowledged_log(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)

    ## error: two parameters
    #
    def test_beacon_sp_two_param(self):

        helper.issue("BeaconSp 100 200")
        # check logs
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.negative_acknowledged_log(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)

    ## error: invalid parameter
    #
    def test_beacon_sp_param_invalid(self):

        helper.issue("BeaconSp test")
        # check logs
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.negative_acknowledged_log(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)

    ## 60 second spacing signed
    #
    def test_beacon_sp_60_signed(self):

        interval = 60
        helper.issue(helper.generate_signed(f"BeaconSp {interval}"))
        # check logs
        log = helper.collect_log()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SBI")
        # verify beacon interval
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)
        # discard messages
        helper.discard_messages()

    ## 120 second spacing signed
    #
    def test_beacon_sp_120_signed(self):

        interval = 120
        helper.issue(helper.generate_signed(f"BeaconSp {interval}"))
        # check logs
        log = helper.collect_log()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SBI")
        # verify beacon interval
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)
        # discard messages
        helper.discard_messages()

    ## 90 second spacing signed
    #
    def test_beacon_sp_90_signed(self):

        interval = 90
        helper.issue(helper.generate_signed(f"BeaconSp {interval}"))
        # check logs
        log = helper.collect_log()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SBI")
        # verify beacon interval
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)
        # discard messages
        helper.discard_messages()

    ## no beacon signed
    #
    def test_beacon_sp_0_signed(self):

        interval = 0
        helper.issue(helper.generate_signed(f"BeaconSp {interval}"))
        # check logs
        log = helper.collect_log()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SBI")
        # verify beacon interval
        log = helper.collect_two_beacons(interval)
        assert helper.beacon_interval(interval, log)
        # discard messages
        helper.discard_messages()

    ## error: no parameter signed
    #
    def test_beacon_sp_no_param_signed(self):

        helper.issue(helper.generate_signed("BeaconSp"))
        # check logs
        log = helper.collect_log()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.negative_acknowledged_log(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)

    ## error: two parameters signed
    #
    def test_beacon_sp_two_param_signed(self):

        helper.issue(helper.generate_signed("BeaconSp 100 200"))
        # check logs
        log = helper.collect_log()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.negative_acknowledged_log(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)

    ## error: invalid parameter signed
    #
    def test_beacon_sp_param_invalid_signed(self):

        helper.issue(helper.generate_signed("BeaconSp test"))
        log = helper.collect_log()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.negative_acknowledged_log(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)
