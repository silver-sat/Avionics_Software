##
# @file test_get_pic_times.py
# @brief Unit test Avionics Board GetPicTimes command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 21 August 2022

"""Unit test Avionics Board GetPicTimes command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test GetPicTimes command
#


class TestGetPicTimes:
    """Test GetPicTimes command"""

    ## get picture times
    #
    def test_get_pic_times(self):

        log = helper.collect("GetPicTimes")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.timestamp_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter
    #
    def test_get_pic_times_param(self):
        log = helper.collect("GetPicTimes test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
