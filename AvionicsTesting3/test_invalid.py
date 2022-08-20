##
# @file test_invalid.py   
# @brief Unit test Avionics Board Invalid command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 20 August 2022

"""Unit test Avionics Board Invalid command"""

import helper
import serial
from collections import namedtuple
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test Invalid command
#

class TestInvalid:
    """Test Invalid command"""
    
    def test_invalid(self):

        log = helper.collect("Invalid")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    def test_invalid_param(self):
        log = helper.collect("Invalid test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    def test_invalid_two_param(self):
        log = helper.collect("Invalid test1 test2")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        
    def test_invalid_six_param(self):
        log = helper.collect("Invalid test1 test2 test3 test4 test5 test6")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    def test_invalid_seven_param(self):
        log = helper.collect("Invalid test1 test2 test3 test4 test5 test6 test7")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
