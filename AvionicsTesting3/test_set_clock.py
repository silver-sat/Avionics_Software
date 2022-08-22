##
# @file test_set_clock.py
# @brief Unit test Avionics Board SetClock command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
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
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## set realtime clock with current time
    #
    def test_set_clock(self):

        utc_time = datetime.now(timezone.utc)
        log = helper.collect("SetClock " + utc_time.strftime("%Y %m %d %H %M %S"))
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## error: incorrect number of parameters
    #
    def test_set_clock_no_param(self):

        log = helper.collect("SetClock")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: incorrect number of parameters
    #
    def test_set_clock_three_param(self):

        log = helper.collect("SetClock 2023 12 12")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters
    #
    def test_set_clock_six_param_invalid(self):

        log = helper.collect("SetClock test1 test2 test3 test4 test5 test6")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters
    #
    def test_set_clock_six_zeros(self):

        log = helper.collect("SetClock 0 0 0 0 0 0")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: time to early
    #
    def test_set_clock_time_too_early(self):

        log = helper.collect("SetClock 2020 10 10 10 10 10")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: time too late
    #
    def test_set_clock_time_too_late(self):

        log = helper.collect("SetClock 2100 3 4 5 6 7")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
