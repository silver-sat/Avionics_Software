##
# @file test_get_comms.py
# @brief Unit test Avionics Board GetComms command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 22 August 2022

"""Unit test Avionics Board GetComms command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test GetComms command
#


class TestGetComms:
    """Test GetComms command"""

    ## get communications status
    #
    def test_get_comms(self):

        log = helper.collect("GetComms")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.local_get_comms_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter
    #
    def test_get_comms_param(self):
        log = helper.collect("GetComms test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
