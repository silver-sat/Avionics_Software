##
# @file test_query_register.py
# @brief FlatSat test Avionics Board QueryRegister command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board QueryRegister command"""

import helper

## Test QueryRegister command
#


class TestQueryRegister:
    """Test QueryRegister command"""

    ## query radio register
    #
    def test_query_register(self):

        helper.issue("QueryRegister 12345")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.local_query_register_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.QUERY_REGISTER)
        helper.respond(helper.RES.encode("utf-8") + helper.QUERY_REGISTER + "123".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RQR")
