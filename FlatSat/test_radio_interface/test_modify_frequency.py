##
# @file test_modify_frequency.py
# @brief FlatSat test Avionics Board ModifyFrequency command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board ModifyFrequency command"""

import helper

## Test ModifyFrequency command
#


class TestModifyFrequency:
    """Test ModifyFrequency command"""

    ## modify frequency
    #
    def test_modify_frequency(self):

        helper.issue("ModifyFrequency 123456789")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.local_modify_frequency_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.MODIFY_FREQ)
        helper.respond(helper.RES.encode("utf-8") + helper.MODIFY_FREQ + "123456789".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RMF")
