##
# @file test_twee_slee.py
# @brief Unit test Avionics Board TweeSlee command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 20 August 2022

"""Unit test Avionics Board TweeSlee command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test TweeSlee command
#


class TestTweeSlee:
    """Test TweeSlee command"""

    ## active payload to sleep
    #
    def test_twee_slee(self):

        log = helper.collect("TweeSlee")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.local_stop_message_sent(log)
        assert helper.payload_power_off(log)

    ## error: invalid parameter
    #
    def test_twee_slee_param(self):
        log = helper.collect("TweeSlee test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## active payload to sleep signed
    #
    def test_twee_slee_signed(self):

        log = helper.collect(helper.generate_signed("TweeSlee"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.local_stop_message_sent(log)
        assert helper.payload_power_off(log)

    ## error: invalid parameter signed
    #
    def test_twee_slee_param_signed(self):
        log = helper.collect(helper.generate_signed("TweeSlee test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
