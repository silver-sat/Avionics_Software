##
# @file test_get_telemetry.py
# @brief Unit test Avionics Board GetTelemetry command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 21 August 2022

"""Unit test Avionics Board GetTelemetry command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test GetTelemetry command
#


class TestGetTelemetry:
    """Test GetTelemetry command"""

    ## get inertial telemetry
    #
    def test_get_telemetry(self):

        log = helper.collect("GetTelemetry")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.telemetry_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter
    #
    def test_get_telemetry_param(self):
        log = helper.collect("GetTelemetry test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
