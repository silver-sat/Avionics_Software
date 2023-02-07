##
# @file test_adjust_frequency.py
# @brief FlatSat test Avionics Board AdjustFrequency command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board AdjustFrequency command"""

import helper

## Test AdjustFrequency command
#


class TestAdjustFrequency:
    """Test AdjustFrequency command"""

    ## adjust frequency
    #
    def test_adjust_frequency(self):

        helper.issue("AdjustFrequency 123456789")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.local_adjust_frequency_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.ADJUST_FREQ)
        helper.respond(helper.RES.encode("utf-8") + helper.ADJUST_FREQ + "123456789".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RAF")
