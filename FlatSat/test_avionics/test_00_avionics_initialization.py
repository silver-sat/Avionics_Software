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

import utility
import time

## Validate Avionics Board initialization log entries
#
class TestAvionicsInitialization:
    """Valiate initialization log messages"""

    ## Validate initization completion
    #
    def test_completion(self):

        log = utility.collect_initialization()
        assert utility.antenna_deployed(log)
        assert utility.initialization_complete(log)
        assert utility.no_logged_errors(log)
        message = utility.collect_message()
        assert utility.fends_received(message)

        """Set the realtime clock"""

    ## Turn off the beacon
    #
    def test_set_beacon_interval(self):

        utility.issue(f"BeaconSp 0")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check message traffic
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")

    ## Set the realtime clock
    #
    def test_set_realtime_clock(self):

        utc_time = time.strftime("%Y %m %d %H %M %S", time.gmtime())
        utility.issue(f"SetClock {utc_time}")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check message traffic
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SRC")
