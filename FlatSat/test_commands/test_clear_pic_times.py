##
# @file test_clear_pic_times.py
# @brief Unit test Avionics Board ClearPicTimes command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 2 October 2022

"""Unit test Avionics Board ClearPicTimes command"""

import helper
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test ClearPicTimes command
#


class TestClearPicTimes:
    """Test ClearPicTimes command"""

    ## clear picture times
    #
    def test_clear_pic_times(self):

        log = helper.collect("PicTimes 2023 11 11 10 10 0")
        log = helper.collect("ClearPicTimes")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        log = helper.collect("GetPicTimes")
        assert helper.pictimes_zero_sent(log)

    ## error: invalid parameter
    #
    def test_clear_pic_times_param(self):
        log = helper.collect("ClearPicTimes test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## clear picture times signed
    #
    def test_clear_pic_times_signed(self):

        log = helper.collect("PicTimes 2023 11 11 10 10 0")
        log = helper.collect(helper.generate_signed("ClearPicTimes"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        log = helper.collect("GetPicTimes")
        assert helper.pictimes_zero_sent(log)

    ## error: invalid parameter signed
    #
    def test_clear_pic_times_param_signed(self):
        log = helper.collect(helper.generate_signed("ClearPicTimes test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
