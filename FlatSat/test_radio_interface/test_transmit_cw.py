##
# @file test_transmit_cw.py
# @brief FlatSat test Avionics Board TransmitCW command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board TransmitCW command"""

import helper

## Test TranmitCW command
#


class TestTransmitCW:
    """Test TransmitCW command"""

    ## transmit carrier wave
    #
    def test_transmit_cw(self):

        helper.issue("TransmitCW 12")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.local_transmit_carrier_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.TRANSMIT_CARRIER)
        helper.respond(helper.RES.encode("utf-8") + helper.TRANSMIT_CARRIER + "CW mode complete".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RTC")
