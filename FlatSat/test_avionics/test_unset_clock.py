##
# @file test_unset_clock.py
# @brief FlatSat test Avionics Board UnsetClock command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.1
# @date 2 February 2023

"""FlatSat test Avionics Board UnsetClock command"""

import utility

## Test UnsetClock command
#
class TestUnsetClock:
    """Test UnsetClock command"""

    ## unset realtime clock
    #
    def test_unset_clock(self):

        utility.issue("UnsetClock")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "URC")

    ## error: incorrect parameter
    #
    def test_unset_clock_param(self):
        utility.issue("UnsetClock clear")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## unset realtime clock signed
    #
    def test_unset_clock_signed(self):

        utility.issue(utility.generate_signed("UnsetClock"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "URC")

    ## error: incorrect parameter signed
    #
    def test_unset_clock_param_signed(self):
        utility.issue(utility.generate_signed("UnsetClock clear"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)
