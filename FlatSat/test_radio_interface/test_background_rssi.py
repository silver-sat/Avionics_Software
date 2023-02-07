##
# @file test_background_rssi.py
# @brief FlatSat test Avionics Board BackgroundRSSI command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board BackgroundRSSI command"""

import helper

## Test BackgroundRSSI command
#


class TestBackgroundRSSI:
    """Test BackgroundRSSI command"""

    ## report background RSSI
    #
    def test_background_rssi(self):

        helper.issue("BackgroundRSSI")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.local_background_rssi_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.BACKGROUND_RSSI)
        helper.respond(helper.RES.encode("utf-8") + helper.BACKGROUND_RSSI + "123".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RBR")
