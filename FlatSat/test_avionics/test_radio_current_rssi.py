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

      ## current RSSI
    #
    def test_current_RSSI(self):

        utility.issue("CurrentRSSI")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_current_RSSI_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_current_RSSI_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.CURRENT_RSSI)
        utility.respond(
            utility.RES.encode("utf-8") + utility.CURRENT_RSSI + " 123".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_current_RSSI_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_current_RSSI_sent(message)

    ## error: incorrect number of parameters
    #
    def test_current_RSSI_param(self):

        utility.issue("CurrentRSSI 1")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: invalid parameter
    #
    def test_current_RSSI_invalid_param(self):

        utility.issue("CurrentRSSI test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)


    ## current RSSI signed
    #
    def test_current_RSSI_signed(self):

        utility.issue(utility.generate_signed("CurrentRSSI"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_current_RSSI_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_current_RSSI_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.CURRENT_RSSI)
        utility.respond(
            utility.RES.encode("utf-8") + utility.CURRENT_RSSI + " 123".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_current_RSSI_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_current_RSSI_sent(message)

    ## error: incorrect number of parameters signed
    #
    def test_current_RSSI_signed_two_param(self):

        utility.issue(utility.generate_signed("CurrentRSSI 1"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: invalid parameter signed
    #
    def test_current_RSSI_signed_invalid_param(self):

        utility.issue(utility.generate_signed("CurrentRSSI test"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    