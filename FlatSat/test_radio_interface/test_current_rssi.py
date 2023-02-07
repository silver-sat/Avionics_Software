##
# @file test_current_rssi.py
# @brief FlatSat test Avionics Board CurrentRSSI command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board CurrentRSSI command"""

import helper

## Test CurrentRSSI command
#


class TestCurrentRSSI:
    """Test CurrentRSSI command"""

    ## report current RSSI
    #
    def test_current_rssi(self):

        helper.issue("CurrentRSSI")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.local_current_rssi_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.CURRENT_RSSI)
        helper.respond(helper.RES.encode("utf-8") + helper.CURRENT_RSSI + "123".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RCR")
