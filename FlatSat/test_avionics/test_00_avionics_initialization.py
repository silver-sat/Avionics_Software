##
# @file test_00_avionics_initialization.py
# @brief Validate Avionics Board initialization log entries
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 13 September 2022
#

# Note: this test must be run first by pytest (before any command tests) to clear
# initialization output. The file name must sort first in the list of tests.
#

"""Validate Avionics Board initialization log entries"""

import helper
from collections import namedtuple
import time

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Validate Avionics Board initialization log entries
#


class TestAvionicsInitialization:
    """Valiate initialization log messages"""

    ## Validate initization completion
    #
    def test_completion(self):
        log = helper.collect_initialization()
        assert helper.initialization_complete(log)
        assert helper.no_logged_errors(log)
        message = helper.collect_message()
        assert helper.fends_received(message)

        """Set the realtime clock"""

    ## Set the realtime clock
    #
    def test_set_realtime_clock(self):

        utc_time = time.strftime("%Y %m %d %H %M %S", time.gmtime());
        helper.issue(f"SetClock {utc_time}")
        # check log
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check message traffic
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SRC")
