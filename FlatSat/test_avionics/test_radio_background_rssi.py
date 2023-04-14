##
# @file test_radio_background_rssi.py
# @brief FlatSat test Avionics Board BackgroundRSSI command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
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

        utility.issue("BackgroundRSSI 12")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_background_RSSI_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_background_RSSI_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.BACKGROUND_RSSI)
        utility.respond(
            utility.RES.encode("utf-8") + utility.BACKGROUND_RSSI + "12".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_background_RSSI_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_background_RSSI_sent(message)

    ## error: incorrect number of parameters
    #
    def test_background_rssi_two_param(self):

        utility.issue("BackgroundRSSI 12 12")
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
    def test_background_rssi_invalid_param(self):

        utility.issue("BackgroundRSSI test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: parameter missing
    #
    def test_background_rssi_missing_param(self):

        utility.issue("BackgroundRSSI")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: parameter length short
    #
    def test_background_rssi_short_param(self):

        utility.issue("BackgroundRSSI 1")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)
   
    ## error: parameter length long
    #
    def test_background_rssi_long_param(self):

        utility.issue("BackgroundRSSI 123")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## report background RSSI signed
    #
    def test_background_rssi_signed(self):

        utility.issue(utility.generate_signed("BackgroundRSSI 12"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_background_RSSI_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_background_RSSI_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.BACKGROUND_RSSI)
        utility.respond(
            utility.RES.encode("utf-8") + utility.BACKGROUND_RSSI + "12".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_background_RSSI_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_background_RSSI_sent(message)

    ## error: incorrect number of parameters signed
    #
    def test_background_rssi_signed_two_param(self):

        utility.issue(utility.generate_signed("BackgroundRSSI 12 12"))
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
    def test_background_rssi_signed_invalid_param(self):

        utility.issue(utility.generate_signed("BackgroundRSSI test"))
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

    ## error: parameter missing signed
    #
    def test_background_rssi_signed_missing_param(self):

        utility.issue(utility.generate_signed("BackgroundRSSI"))
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
    
    ## error: parameter short signed
    #
    def test_background_rssi_signed_short_param(self):

        utility.issue(utility.generate_signed("BackgroundRSSI 1"))
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

    ## error: parameter length long signed
    #
    def test_background_rssi_signed_long_param(self):

        utility.issue(utility.generate_signed("BackgroundRSSI 123"))
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
