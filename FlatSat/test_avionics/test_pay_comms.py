##
# @file test_pay_comms.py
# @brief FlatSat test Avionics Board PayComms command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board PayComms command"""

import helper

## Test PayComms command
#


class TestPayComms:
    """Test PayComms command"""

    ## start payload communications
    #
    def test_pay_comms(self):

        helper.issue("PayComms")
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "PYC")