##
# @file test_unswet_realtime_clock.py
# @brief FlatSat test Avionics Board UnsetClock command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 2 February 2023

"""FlatSat test Avionics Board UnsetClock command"""

import helper

## Test UnsetClock command
#


class TestUnsetClock:
    """Test UnsetClock command"""

    ## unset realtime clock
    #
    def test_unsset_realtime_clock(self):

        helper.issue("UnsetClock")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message)

