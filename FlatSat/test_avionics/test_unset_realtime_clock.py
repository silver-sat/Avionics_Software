##
# @file test_unset_realtime_clock.py
# @brief FlatSat test Avionics Board UnsetClock command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 2 February 2023

"""FlatSat test Avionics Board UnsetClock command"""

import utility

## Test UnsetClock command
#
class TestUnsetClock:
    """Test UnsetClock command"""

    ## unset realtime clock
    #
    def test_unsset_realtime_clock(self):

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

