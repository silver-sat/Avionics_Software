##
# @file test_get_power.py   
# @brief Unit test Avionics Board GetPower command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 22 August 2022

"""Unit test Avionics Board GetPower command"""

import helper
import serial
from collections import namedtuple
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test GetPower command
#

class TestGetPower:
    """Test GetPower command"""
    
    def test_get_power(self):

        log = helper.collect("GetPower")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.power_sent(log)
        assert helper.executed(log)

    def test_get_power_param(self):
        log = helper.collect("GetPower test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
