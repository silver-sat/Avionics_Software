##
# @file test_twee_slee.py   
# @brief Unit test Avionics Board TweeSlee command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 20 August 2022

"""Unit test Avionics Board TweeSlee command"""

import helper
import serial
from collections import namedtuple
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test TweeSlee command
#

class TestTweeSlee:
    """Test TweeSlee command"""
    
    def test_twee_slee(self):

        log = helper.collect_through_power_off("TweeSlee")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.local_stop_message_sent(log)
        assert helper.payload_power_off(log)

    def test_twee_slee_param(self):
        log = helper.collect("TweeSlee test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
