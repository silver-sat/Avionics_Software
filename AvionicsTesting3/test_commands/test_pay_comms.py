##
# @file test_pay_comms.py
# @brief Unit test Avionics Board PayComms command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 21 August 2022

"""Unit test Avionics Board PayComms command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test PayComms command
#


class TestPayComms:
    """Test PayComms command"""

    ## start payload communications
    #
    def test_pay_comms(self):

        log = helper.collect_through_power_off("PayComms")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.payload_power_off(log)

    ## error: invalid parameter
    #
    def test_pay_comms_param(self):
        log = helper.collect("PayComms test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## start payload communications signed
    #
    def test_pay_comms_signed(self):

        log = helper.collect_through_power_off(helper.generate_signed("PayComms"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.payload_power_off(log)

    ## error: invalid parameter signed
    #
    def test_pay_comms_param_signed(self):
        log = helper.collect(helper.generate_signed("PayComms test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
