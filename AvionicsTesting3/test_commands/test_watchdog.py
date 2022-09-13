##
# @file test_watchdog.py
# @brief Unit test Avionics Board Watchdog command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 21 August 2022

# This test verifies that a hardware pin is set low, but does not use or require the reset
# pin of the SAMD21

"""Unit test Avionics Board Watchdog command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test Watchdog command
#


class TestWatchdog:
    """Test Watchdog command"""

    ## trigger watchdog
    #
    def test_watchdog(self):

        log = helper.collect_through_reset_pin_cleared("Watchdog")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.reset_pin_set(log)
        assert helper.reset_pin_cleared(log)

    ## error: invalid parameter
    #
    def test_watchdog_param(self):
        log = helper.collect("Watchdog test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## trigger watchdog signed
    #
    def test_watchdog_signed(self):

        log = helper.collect_through_reset_pin_cleared(helper.generate_signed("Watchdog"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.reset_pin_set(log)
        assert helper.reset_pin_cleared(log)

    ## error: invalid parameter signed
    #
    def test_watchdog_param_signed(self):
        log = helper.collect(helper.generate_signed("Watchdog test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
