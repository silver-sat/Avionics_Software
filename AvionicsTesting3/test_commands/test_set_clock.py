##
# @file test_set_clock.py
# @brief Unit test Avionics Board SetClock command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 21 August 2022

"""Unit test Avionics Board SetClock command"""

import helper
import serial
from collections import namedtuple
from datetime import datetime
from datetime import timezone

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test SetClock command
#


class TestSetClock:
    """Test SetClock command"""

    ## set realtime clock
    #
    def test_set_clock_early(self):

        log = helper.collect("SetClock 2022 1 1 10 10 0")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## set realtime clock with current time
    #
    def test_set_clock(self):

        utc_time = datetime.now(timezone.utc)
        log = helper.collect("SetClock " + utc_time.strftime("%Y %m %d %H %M %S"))
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## error: incorrect number of parameters
    #
    def test_set_clock_no_param(self):

        log = helper.collect("SetClock")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: incorrect number of parameters
    #
    def test_set_clock_three_param(self):

        log = helper.collect("SetClock 2023 12 12")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters
    #
    def test_set_clock_six_param_invalid(self):

        log = helper.collect("SetClock test1 test2 test3 test4 test5 test6")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters
    #
    def test_set_clock_six_zeros(self):

        log = helper.collect("SetClock 0 0 0 0 0 0")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: time to early
    #
    def test_set_clock_time_too_early(self):

        log = helper.collect("SetClock 2020 10 10 10 10 10")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: time too late
    #
    def test_set_clock_time_too_late(self):

        log = helper.collect("SetClock 2100 3 4 5 6 7")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## set realtime clock signed
    #
    def test_set_clock_early_signed(self):

        log = helper.collect(helper.generate_signed("SetClock 2022 1 1 10 10 0"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## set realtime clock with current time signed
    #
    def test_set_clock_signed(self):

        utc_time = datetime.now(timezone.utc)
        log = helper.collect(helper.generate_signed("SetClock " + utc_time.strftime("%Y %m %d %H %M %S")))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## error: incorrect number of parameters signed
    #
    def test_set_clock_no_param_signed(self):

        log = helper.collect(helper.generate_signed("SetClock"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: incorrect number of parameters signed
    #
    def test_set_clock_three_param_signed(self):

        log = helper.collect(helper.generate_signed("SetClock 2023 12 12"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters signed
    #
    def test_set_clock_six_param_invalid_signed(self):

        log = helper.collect(helper.generate_signed("SetClock test1 test2 test3 test4 test5 test6"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters signed
    #
    def test_set_clock_six_zeros_signed(self):

        log = helper.collect(helper.generate_signed("SetClock 0 0 0 0 0 0"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: time to early signed
    #
    def test_set_clock_time_too_early_signed(self):

        log = helper.collect(helper.generate_signed("SetClock 2020 10 10 10 10 10"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: time too late
    #
    def test_set_clock_time_too_late_signed(self):

        log = helper.collect(helper.generate_signed("SetClock 2100 3 4 5 6 7"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
