##
# @file test_radio_transmit_cw.py
# @brief FlatSat test Avionics Board TransmitCW command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board TransmitCW command"""

import utility

## Test TranmitCW command
#


class TestTransmitCW:
    """Test TransmitCW command"""

    ## transmit CW
    #
    def test_transmit_CW(self):

        utility.issue("TransmitCW 12")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_transmit_CW_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_transmit_CW_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.TRANSMIT_CARRIER)
        utility.respond(
            utility.RES.encode("utf-8") + utility.TRANSMIT_CARRIER + " 12".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_transmit_CW_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_transmit_CW_sent(message)

    ## error: incorrect number of parameters
    #
    def test_transmit_CW_two_param(self):

        utility.issue("TransmitCW 12 12")
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
    def test_transmit_CW_invalid_param(self):

        utility.issue("TransmitCW test")
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
    def test_transmit_CW_missing_param(self):

        utility.issue("TransmitCW")
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
    def test_transmit_CW_short_param(self):

        utility.issue("TransmitCW 1")
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
    def test_transmit_CW_long_param(self):

        utility.issue("TransmitCW 123")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## transmit CW signed
    #
    def test_transmit_CW_signed(self):

        utility.issue(utility.generate_signed("TransmitCW 12"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_transmit_CW_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_transmit_CW_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.TRANSMIT_CARRIER)
        utility.respond(
            utility.RES.encode("utf-8") + utility.TRANSMIT_CARRIER + " 12".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_transmit_CW_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_transmit_CW_sent(message)

    ## error: incorrect number of parameters signed
    #
    def test_transmit_CW_signed_two_param(self):

        utility.issue(utility.generate_signed("TransmitCW 12 12"))
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
    def test_transmit_CW_signed_invalid_param(self):

        utility.issue(utility.generate_signed("TransmitCW test"))
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
    def test_transmit_CW_signed_missing_param(self):

        utility.issue(utility.generate_signed("TransmitCW"))
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
    def test_transmit_CW_signed_short_param(self):

        utility.issue(utility.generate_signed("TransmitCW 1"))
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
    def test_transmit_CW_signed_long_param(self):

        utility.issue(utility.generate_signed("TransmitCW 123"))
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
