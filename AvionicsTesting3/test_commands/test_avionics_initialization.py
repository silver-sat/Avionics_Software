##
# @file test_avionics_initialization.py
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

        """Set the realtime clock"""

    ## Set the realtime clock
    #
    def test_set_realtime_clock(self):

        utc_time = time.strftime("%Y %m %d %H %M %S", time.gmtime());
        log = helper.collect(f"SetClock {utc_time}")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
