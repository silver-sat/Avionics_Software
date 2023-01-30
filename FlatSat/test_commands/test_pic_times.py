##
# @file test_pic_times.py
# @brief Unit test Avionics Board PicTimes command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 20 August 2022

"""Unit test Avionics Board PicTimes command"""

import helper
import serial
from collections import namedtuple
import time

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test PicTimes command
#


class TestPicTimes:
    """Test PicTimes command"""

    ## set picture times
    #
    def test_pic_times(self):
        start_time = time.gmtime(time.time() + 10)
        start_time = time.strftime("%Y %m %d %H %M %S", start_time)
        log = helper.collect_through_power_off(f"PicTimes {start_time}")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.payload_power_off(log)

    ## error: incorrect number of parameters
    #
    def test_pic_times_no_param(self):

        log = helper.collect("PicTimes")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: incorrect number of parameters
    #
    def test_pic_times_three_param(self):

        log = helper.collect("PicTimes 2023 12 12")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters
    #
    def test_pic_times_six_param_invalid(self):

        log = helper.collect("PicTimes test1 test2 test3 test4 test5 test6")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters
    #
    def test_pic_times_six_zeros(self):

        log = helper.collect("PicTimes 0 0 0 0 0 0")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: date too early
    #
    def test_pic_times_time_too_early(self):

        log = helper.collect("PicTimes 2020 10 10 10 10 10")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: date too late
    #
    def test_pic_times_time_too_late(self):

        log = helper.collect("PicTimes 2100 3 4 5 6 7")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## set picture times signed
    #
    def test_pic_times_signed(self):

        start_time = time.gmtime(time.time() + 10)
        start_time = time.strftime("%Y %m %d %H %M %S", start_time)
        log = helper.collect_through_power_off(helper.generate_signed(f"PicTimes {start_time}"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        assert helper.payload_power_off(log)

    ## error: no parameters signed
    #
    def test_pic_times_no_param_signed(self):

        log = helper.collect(helper.generate_signed("PicTimes"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: three parameters signed
    #
    def test_pic_times_three_param_signed(self):

        log = helper.collect(helper.generate_signed("PicTimes 2023 12 12"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters signed
    #
    def test_pic_times_six_param_invalid_signed(self):

        log = helper.collect(
            helper.generate_signed("PicTimes test1 test2 test3 test4 test5 test6")
        )
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters signed
    #
    def test_pic_times_six_zeros_signed(self):

        log = helper.collect(helper.generate_signed("PicTimes 0 0 0 0 0 0"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: date too early signed
    #
    def test_pic_times_time_too_early_signed(self):

        log = helper.collect(helper.generate_signed("PicTimes 2020 10 10 10 10 10"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: date too late signed
    #
    def test_pic_times_time_too_late_signed(self):

        log = helper.collect(helper.generate_signed("PicTimes 2100 3 4 5 6 7"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
