##
# @file test_radio_sweep_receiver.py
# @brief FlatSat test Avionics Board SweepReceiver command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board SweepReceiver command"""

import utility

## Test SweepReceiver command
#


class TestSweepReceiver:
    """Test SweepReceiver command"""

    ## sweep receiver
    #
    def test_sweep_receiver(self):

        utility.issue("SweepReceiver 123456789 123456789 123 123")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_sweep_receiver_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_sweep_receiver_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_RECEIVER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123".encode("utf-8")
            + "123455789".encode("utf-8")
            + "123".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_sweep_receiver_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_sweep_receiver_sent(message)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123".encode("utf-8")
            + "123455789".encode("utf-8")
            + "123".encode("utf-8")
        )
        message = utility.collect_message()
        assert utility.message_remote_sweep_receiver_sent(message)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123".encode("utf-8")
            + "123455789".encode("utf-8")
            + "123".encode("utf-8")
        )
        message = utility.collect_message()
        assert utility.message_remote_sweep_receiver_sent(message)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123".encode("utf-8")
            + "123455789".encode("utf-8")
            + "123".encode("utf-8")
        )
        message = utility.collect_message()
        assert utility.message_remote_sweep_receiver_sent(message)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123".encode("utf-8")
            + "123455789".encode("utf-8")
            + "123".encode("utf-8")
        )
        message = utility.collect_message()
        assert utility.message_remote_sweep_receiver_sent(message)

    ## error: incorrect number of parameters
    #
    def test_sweep_receiver_two_param(self):

        utility.issue("SweepReceiver 123456789 123456789")
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
    def test_sweep_receiver_invalid_param(self):

        utility.issue("SweepReceiver test")
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
    def test_sweep_receiver_missing_param(self):

        utility.issue("SweepReceiver")
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
    def test_sweep_receiver_short_param(self):

        utility.issue("SweepReceiver 12345678 123456789 123 123")
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
    def test_sweep_receiver_third_short_param(self):

        utility.issue("SweepReceiver 123456789 123456789 12 123")
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
    def test_sweep_receiver_long_param(self):

        utility.issue("SweepReceiver 1234567890 123456789 123 123")
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
    def test_sweep_receiver_fourth_long_param(self):

        utility.issue("SweepReceiver 123456789 123456789 123 1234")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## sweep receiver signed
    #
    def test_sweep_receiver_signed(self):

        utility.issue(
            utility.generate_signed("SweepReceiver 123456789 123456789 123 123")
        )
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_sweep_receiver_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_sweep_receiver_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_RECEIVER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123".encode("utf-8")
            + "123455789".encode("utf-8")
            + "123".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_sweep_receiver_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_sweep_receiver_sent(message)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123".encode("utf-8")
            + "123455789".encode("utf-8")
            + "123".encode("utf-8")
        )
        message = utility.collect_message()
        assert utility.message_remote_sweep_receiver_sent(message)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123".encode("utf-8")
            + "123455789".encode("utf-8")
            + "123".encode("utf-8")
        )
        message = utility.collect_message()
        assert utility.message_remote_sweep_receiver_sent(message)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123".encode("utf-8")
            + "123455789".encode("utf-8")
            + "123".encode("utf-8")
        )
        message = utility.collect_message()
        assert utility.message_remote_sweep_receiver_sent(message)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123".encode("utf-8")
            + "123455789".encode("utf-8")
            + "123".encode("utf-8")
        )
        message = utility.collect_message()
        assert utility.message_remote_sweep_receiver_sent(message)

    ## error: incorrect number of parameters signed
    #
    def test_sweep_receiver_signed_two_param(self):

        utility.issue(utility.generate_signed("SweepReceiver 123456789 123456789"))
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
    def test_sweep_receiver_signed_invalid_param(self):

        utility.issue(utility.generate_signed("SweepReceiver test"))
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
    def test_sweep_receiver_signed_missing_param(self):

        utility.issue(utility.generate_signed("SweepReceiver"))
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
    def test_sweep_receiver_signed_short_param(self):

        utility.issue(
            utility.generate_signed("SweepReceiver 12345678 123456789 123 123")
        )
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
    def test_sweep_receiver_signed_third_short_param(self):

        utility.issue(
            utility.generate_signed("SweepReceiver 123456789 123456789 12 123")
        )
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
    def test_sweep_receiver_signed_long_param(self):

        utility.issue(
            utility.generate_signed("SweepReceiver 1234567890 123456789 123 123")
        )
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
    def test_sweep_receiver_signed_fourth_long_param(self):

        utility.issue(
            utility.generate_signed("SweepReceiver 123456789 123456789 123 1234")
        )
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
