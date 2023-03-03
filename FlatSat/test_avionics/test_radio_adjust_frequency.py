##
# @file test_radio_adjust_frequency.py
# @brief FlatSat test Avionics Board AdjustFrequency command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 7 February 2023

"""FlatSat test Avionics Board AdjustFrequency command"""

import utility

## Test AdjustFrequency command
#
class TestAdjustFrequency:
    """Test AdjustFrequency command"""

    ## adjust frequency
    #
    def test_adjust_frequency(self):

        utility.issue("AdjustFrequency 123456789")
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
        assert utility.local_adjust_frequency_message_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.ADJUST_FREQ)
        utility.respond(utility.RES.encode("utf-8") + utility.ADJUST_FREQ + "123456789".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RAF")
