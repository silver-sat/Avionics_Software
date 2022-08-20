##
# @file test_pic_times.py   
# @brief Unit test Avionics Board PicTimes command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 20 August 2022

"""Unit test Avionics Board PicTimes command"""

import helper
import serial
from collections import namedtuple
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test PicTimes command
#

class TestPicTimes:
    """Test PicTimes command"""
    
    def test_pic_times(self):

        log = helper.collect("PicTimes 2023 12 12 10 10 0")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    def test_pic_times_no_param(self):

        log = helper.collect("PicTimes")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    def test_pic_times_three_param(self):

        log = helper.collect("PicTimes 2023 12 12")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        
    def test_pic_times_six_param_invalid(self):

        log = helper.collect("PicTimes test1 test2 test3 test4 test5 test6")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    def test_pic_times_six_zeros(self):

        log = helper.collect("PicTimes 0 0 0 0 0 0")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    def test_pic_times_time_too_early(self):

        log = helper.collect("PicTimes 1900 10 10 10 10 10")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    def test_pic_times_time_too_late(self):

        log = helper.collect("PicTimes 2101 3 4 5 6 7")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
