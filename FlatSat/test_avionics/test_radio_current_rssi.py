##
# @file test_radio_current_rssi.py
# @brief FlatSat test Avionics Board CurrentRSSI command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 7 February 2023

"""FlatSat test Avionics Board CurrentRSSI command"""

import utility

## Test CurrentRSSI command
#


class TestCurrentRSSI:
    """Test CurrentRSSI command"""

    ## report current RSSI
    #
    def test_current_rssi(self):

        utility.issue("CurrentRSSI")
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
        assert utility.local_current_rssi_message_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.CURRENT_RSSI)
        utility.respond(utility.RES.encode("utf-8") + utility.CURRENT_RSSI + "123".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RCR")
