##
# @file test_radio_query_register.py
# @brief FlatSat test Avionics Board QueryRegister command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 7 February 2023

"""FlatSat test Avionics Board QueryRegister command"""

import utility

## Test QueryRegister command
#
class TestQueryRegister:
    """Test QueryRegister command"""

    ## query radio register
    #
    def test_query_register(self):

        utility.issue("QueryRegister 12345")
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
        assert utility.local_query_register_message_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.QUERY_REGISTER)
        utility.respond(utility.RES.encode("utf-8") + utility.QUERY_REGISTER + "123".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RQR")
