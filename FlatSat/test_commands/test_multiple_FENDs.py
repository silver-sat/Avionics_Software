##
# @file test_multiple_FENDs.py
# @brief Unit test Avionics Board multiple FENDs
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 22 October 2022

"""Unit test Avionics Board multiples FENDs"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test incomplete commands
#


class TestMultipleFENDs:
    """Test Multiple FENDs"""

    ## single FEND followed by complete command
    #
    def test_single_FEND(self):
        helper.send_FEND(1)
        log = helper.collect("NoOperate")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## two FENDs followed by complete command
    #
    def test_two_FENDs(self):
        helper.send_FEND(2)
        log = helper.collect("NoOperate")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## three FENDs followed by complete command
    #
    def test_three_FENDs(self):
        helper.send_FEND(3)
        log = helper.collect("NoOperate")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## five FENDs followed by complete command
    #
    def test_five_FENDs(self):
        helper.send_FEND(5)
        log = helper.collect("NoOperate")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
