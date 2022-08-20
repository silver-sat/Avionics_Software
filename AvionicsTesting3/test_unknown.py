##
# @file test_unknown.py   
# @brief Unit test Avionics Board Unknown command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 20 August 2022

"""Unit test Avionics Board Unknown command"""

import helper
import serial
from collections import namedtuple
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test Unknown command
#

class TestNoOperate:
    """Test NoOperate command"""
    
    def test_unknown(self):

        log = helper.collect("Unknown")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        
    def test_unknown_param(self):

        log = helper.collect("Unknown test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    def test_unknown_get_random(self):
        log = helper.collect("GetRandom")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        
    def test_unknown_get_random_param(self):
        log = helper.collect("GetRandom test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
