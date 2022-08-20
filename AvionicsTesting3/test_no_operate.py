##
# @file test_no_operate.py   
# @brief Unit test Avionics Board NoOperate command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 20 August 2022

"""Unit test Avionics Board NoOperate command"""

import helper
import serial
from collections import namedtuple
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test NoOperate command
#

class TestNoOperate:
    """Test NoOperate command"""
    
    def test_no_operate(self):

        log = helper.collect("NoOperate")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    def test_no_operate_param(self):
        log = helper.collect("NoOperate test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        
    def test_no_operate_six_param(self):
        log = helper.collect("NoOperate test1 test2 test3 test4 test5 test6")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
