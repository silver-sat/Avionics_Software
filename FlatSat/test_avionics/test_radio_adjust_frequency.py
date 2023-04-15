##
# @file test_radio_adjust_frequency.py
# @brief FlatSat test Avionics Board AdjustFrequency command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board AdjustFrequency command"""

import utility

## Test AdjustFrequency command
#
class TestAdjustFrequency:
    """Test AdjustFrequency command"""

    ## adjust frequency
    #
    def test_adjust_frequency(self):

        utility.issue("AdjustFrequency 123456789")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_adjust_frequency_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_adjust_frequency_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.ADJUST_FREQ)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.ADJUST_FREQ
            + " 123456789".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_adjust_frequency_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_adjust_frequency_sent(message)

    ## error: incorrect number of parameters
    #
    def test_adjust_frequency_two_param(self):

        utility.issue("AdjustFrequency 123456789 123456789")
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
    def test_adjust_frequency_invalid_param(self):

        utility.issue("AdjustFrequency test")
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
    def test_adjust_frequency_missing_param(self):

        utility.issue("AdjustFrequency")
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
    def test_adjust_frequency_short_param(self):

        utility.issue("AdjustFrequency 12345678")
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
    def test_adjust_frequency_long_param(self):

        utility.issue("AdjustFrequency 1234567890")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## adjust frequency signed
    #
    def test_adjust_frequency_signed(self):

        utility.issue(utility.generate_signed("AdjustFrequency 123456789"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_adjust_frequency_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_adjust_frequency_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.ADJUST_FREQ)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.ADJUST_FREQ
            + " 123456789".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_adjust_frequency_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_adjust_frequency_sent(message)

    ## error: incorrect number of parameters signed
    #
    def test_adjust_frequency_signed_two_param(self):

        utility.issue(utility.generate_signed("AdjustFrequency 123456789 123456789"))
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
    def test_adjust_frequency_signed_invalid_param(self):

        utility.issue(utility.generate_signed("AdjustFrequency test"))
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
    def test_adjust_frequency_signed_missing_param(self):

        utility.issue(utility.generate_signed("AdjustFrequency"))
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
    def test_adjust_frequency_signed_short_param(self):

        utility.issue(utility.generate_signed("AdjustFrequency 12345678"))
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
    def test_adjust_frequency_signed_long_param(self):

        utility.issue(utility.generate_signed("AdjustFrequency 1234567890"))
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

