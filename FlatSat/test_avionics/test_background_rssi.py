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
        #check log
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        #check message traffic
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.local_background_rssi_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.BACKGROUND_RSSI)
        helper.respond(helper.RES.encode("utf-8") + helper.BACKGROUND_RSSI + "123".encode("utf-8"))
        message = helper.collect_message()
        assert helper.response_sent(message, "RBR")
