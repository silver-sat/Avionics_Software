##
# @file test_watchdog.py
# @brief FlatSat test Avionics Board Watchdog command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

# This test verifies that a hardware pin is set low, but does not use or require the reset
# pin of the SAMD21

"""FlatSat test Avionics Board Watchdog command"""

import utility

## Test Watchdog command
#
class TestWatchdog:
    """Test Watchdog command"""

    ## trigger watchdog
    #
    def test_watchdog(self):

        utility.issue("Watchdog")
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "WDG")
        message = utility.collect_message()
        assert utility.reset()

    ## trigger watchdog signed
    #
    def test_watchdog_signed(self):

        utility.issue(utility.generate_signed("Watchdog"))
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "WDG")
        message = utility.collect_message()
        assert utility.reset()
   
    ## trigger watchdog
    #
    def test_watchdog(self):

        utility.issue("Watchdog")
        # check log
        log = utility.collect_through_reset_pin_cleared()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert utility.executed(log)
        assert utility.reset_pin_set(log)
        assert utility.reset_pin_cleared(log)

    ## error: invalid parameter
    #
    def test_watchdog_param(self):
        
        log = utility.collect_log("Watchdog test")
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)

    ## trigger watchdog signed
    #
    def test_watchdog_signed(self):

        utility.issue(utility.generate_signed("Watchdog"))
        log = utility.collect_through_reset_pin_cleared()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert utility.executed(log)
        assert utility.reset_pin_set(log)
        assert utility.reset_pin_cleared(log)

    ## error: invalid parameter signed
    #
    def test_watchdog_param_signed(self):
        log = utility.collect_log(utility.generate_signed("Watchdog test"))
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
