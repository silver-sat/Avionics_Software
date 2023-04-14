##
# @file test_radio_sweep_transmitter.py
# @brief FlatSat test Avionics Board SweepTransmitter command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board SweepTransmitter command"""

import utility

## Test SweepTransmitter command
#s


class TestSweepTransmitter:
    """Test SweepTransmitter command"""


    ## sweep transmitter
    #
    def test_sweep_transmitter(self):

        utility.issue("SweepTransmitter 123456789 123456789 123 123")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_sweep_transmitter_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_sweep_transmitter_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_TRANSMITTER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_TRANSMITTER
            + "sweep done".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_sweep_transmitter_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_sweep_transmitter_sent(message)

    ## error: incorrect number of parameters
    #
    def test_sweep_transmitter_two_param(self):

        utility.issue("SweepTransmitter 123456789 123456789")
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
    def test_sweep_transmitter_invalid_param(self):

        utility.issue("SweepTransmitter test")
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
    def test_sweep_transmitter_missing_param(self):

        utility.issue("SweepTransmitter")
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
    def test_sweep_transmitter_short_param(self):

        utility.issue("SweepTransmitter 12345678 123456789 123 123")
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
    def test_sweep_transmitter_third_short_param(self):

        utility.issue("SweepTransmitter 123456789 123456789 12 123")
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
    def test_sweep_transmitter_long_param(self):

        utility.issue("SweepTransmitter 1234567890 123456789 123 123")
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
    def test_sweep_transmitter_fourth_long_param(self):

        utility.issue("SweepTransmitter 123456789 123456789 123 1234")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## sweep transmitter signed
    #
    def test_sweep_transmitter_signed(self):

        utility.issue(utility.generate_signed("SweepTransmitter 123456789 123456789 123 123"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_sweep_transmitter_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_sweep_transmitter_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_TRANSMITTER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_TRANSMITTER
            + "sweep done".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_sweep_transmitter_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_sweep_transmitter_sent(message)

    ## error: incorrect number of parameters signed
    #
    def test_sweep_transmitter_signed_two_param(self):

        utility.issue(utility.generate_signed("SweepTransmitter 123456789 123456789"))
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
    def test_sweep_transmitter_signed_invalid_param(self):

        utility.issue(utility.generate_signed("SweepTransmitter test"))
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
    def test_sweep_transmitter_signed_missing_param(self):

        utility.issue(utility.generate_signed("SweepTransmitter"))
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

    ## error: parameter length short signed
    #
    def test_sweep_transmitter_signed_short_param(self):

        utility.issue(utility.generate_signed("SweepTransmitter 12345678 123456789 123 123"))
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

    ## error: parameter length short signed
    #
    def test_sweep_transmitter_signed_third_short_param(self):

        utility.issue(utility.generate_signed("SweepTransmitter 123456789 123456789 12 123"))
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
    def test_sweep_transmitter_signed_long_param(self):

        utility.issue(utility.generate_signed("SweepTransmitter 1234567890 123456789 123 123"))
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
    def test_sweep_transmitter_signed_fourth_long_param(self):

        utility.issue(utility.generate_signed("SweepTransmitter 123456789 123456789 123 1234"))
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
