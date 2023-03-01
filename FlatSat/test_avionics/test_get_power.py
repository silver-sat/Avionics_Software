##
# @file test_get_power.py
# @brief FlatSat test Avionics Board GetPower command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board GetPower command"""

import helper

## Test GetPower command
#


class TestGetPower:
    """Test GetPower command"""

    ## get power information
    #
    def test_get_power(self):

        helper.issue("GetPower")
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "GPW")
