##
# @file test_watchdog.py
# @brief FlatSat test Avionics Board Watchdog command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board Watchdog command"""

import helper

## Test Watchdog command
#


class TestWatchdog:
    """Test Watchdog command"""

    ## trigger watchdog
    #
    def test_watchdog(self):

        helper.issue("Watchdog")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message, "WDG")
        message = helper.collect()
        assert helper.reset()

    ## trigger watchdog signed
    #
    def test_watchdog_signed(self):

        helper.issue(helper.generate_signed("Watchdog"))
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message, "WDG")
        message = helper.collect()
        assert helper.reset()
