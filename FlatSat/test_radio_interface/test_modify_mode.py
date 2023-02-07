##
# @file test_modify_mode.py
# @brief FlatSat test Avionics Board ModifyMode command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board ModifyMode command"""

import helper

## Test ModifyMode command
#


class TestModifyMode:
    """Test ModifyFrequency command"""

    ## modify mode
    #
    def test_modify_mode(self):

        helper.issue("ModifyMode 1")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.local_modify_mode_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.MODIFY_MODE)
        helper.respond(helper.RES.encode("utf-8") + helper.MODIFY_MODE + "1".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RMM")
