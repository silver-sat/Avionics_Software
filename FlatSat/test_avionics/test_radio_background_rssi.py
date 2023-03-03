##
# @file test_radio_background_rssi.py
# @brief FlatSat test Avionics Board BackgroundRSSI command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 7 February 2023

"""FlatSat test Avionics Board BackgroundRSSI command"""

import utility

## Test BackgroundRSSI command
#


class TestBackgroundRSSI:
    """Test BackgroundRSSI command"""

    ## report background RSSI
    #
    def test_background_rssi(self):

        utility.issue("BackgroundRSSI")
        #check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        #check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.local_background_rssi_message_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.BACKGROUND_RSSI)
        utility.respond(utility.RES.encode("utf-8") + utility.BACKGROUND_RSSI + "123".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RBR")
