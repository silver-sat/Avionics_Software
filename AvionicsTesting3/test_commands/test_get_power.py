##
# @file test_get_power.py
# @brief Unit test Avionics Board GetPower command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 22 August 2022

"""Unit test Avionics Board GetPower command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test GetPower command
#


class TestGetPower:
    """Test GetPower command"""

    ## get power information
    #
    def test_get_power(self):

        log = helper.collect("GetPower")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.power_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter
    #
    def test_get_power_param(self):
        log = helper.collect("GetPower test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## get power information signed
    #
    def test_get_power_signed(self):

        log = helper.collect(helper.generate_signed("GetPower"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.power_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter signed
    #
    def test_get_power_param_signed(self):
        log = helper.collect(helper.generate_signed("GetPower test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
