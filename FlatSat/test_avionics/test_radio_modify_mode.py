##
# @file test_radio_modify_mode.py
# @brief FlatSat test Avionics Board ModifyMode command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 7 February 2023

"""FlatSat test Avionics Board ModifyMode command"""

import utility

## Test ModifyMode command
#
class TestModifyMode:
    """Test ModifyFrequency command"""

    ## modify mode
    #
    def test_modify_mode(self):

        utility.issue("ModifyMode 1")
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
        assert utility.local_modify_mode_message_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_MODE)
        utility.respond(utility.RES.encode("utf-8") + utility.MODIFY_MODE + "1".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RMM")
