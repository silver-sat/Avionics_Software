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
        # check log
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.local_adjust_frequency_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.ADJUST_FREQ)
        helper.respond(helper.RES.encode("utf-8") + helper.ADJUST_FREQ + "123456789".encode("utf-8"))
        message = helper.collect_message()
        assert helper.response_sent(message, "RAF")
