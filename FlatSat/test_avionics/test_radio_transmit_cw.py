##
# @file test_radio_transmit_cw.py
# @brief FlatSat test Avionics Board TransmitCW command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 7 February 2023

"""FlatSat test Avionics Board TransmitCW command"""

import utility

## Test TranmitCW command
#


class TestTransmitCW:
    """Test TransmitCW command"""

    ## transmit carrier wave
    #
    def test_transmit_cw(self):

        utility.issue("TransmitCW 12")
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
        assert utility.local_transmit_carrier_message_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.TRANSMIT_CARRIER)
        utility.respond(utility.RES.encode("utf-8") + utility.TRANSMIT_CARRIER + "CW mode complete".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RTC")
