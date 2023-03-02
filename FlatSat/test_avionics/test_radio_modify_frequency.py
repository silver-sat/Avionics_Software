##
# @file test_radio_modify_frequency.py
# @brief FlatSat test Avionics Board ModifyFrequency command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 7 February 2023

"""FlatSat test Avionics Board ModifyFrequency command"""

import utility

## Test ModifyFrequency command
#
class TestModifyFrequency:
    """Test ModifyFrequency command"""

    ## modify frequency
    #
    def test_modify_frequency(self):

        utility.issue("ModifyFrequency 123456789")
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
        assert utility.local_modify_frequency_message_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_FREQ)
        utility.respond(utility.RES.encode("utf-8") + utility.MODIFY_FREQ + "123456789".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RMF")
