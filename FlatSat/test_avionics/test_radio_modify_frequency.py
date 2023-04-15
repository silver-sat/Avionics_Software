##
# @file test_radio_modify_frequency.py
# @brief FlatSat test Avionics Board ModifyFrequency command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board ModifyFrequency command"""

import utility

## Test ModifyFrequency command
#
class TestModifyFrequency:
    """Test ModifyFrequency command"""

    ## modify frequency
    #
    def test_modify_frequency(self):

        utility.issue("ModifyFrequency 123456789")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_modify_frequency_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_modify_frequency_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_FREQ)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.MODIFY_FREQ
            + " 123456789".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_modify_frequency_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_modify_frequency_sent(message)

    ## error: incorrect number of parameters
    #
    def test_modify_frequency_two_param(self):

        utility.issue("ModifyFrequency 123456789 123456789")
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
    def test_modify_frequency_invalid_param(self):

        utility.issue("ModifyFrequency test")
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
    def test_modify_frequency_missing_param(self):

        utility.issue("ModifyFrequency")
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
    def test_modify_frequency_short_param(self):

        utility.issue("ModifyFrequency 12345678")
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
    def test_modify_frequency_long_param(self):

        utility.issue("ModifyFrequency 1234567890")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## modify frequency signed
    #
    def test_modify_frequency_signed(self):

        utility.issue(utility.generate_signed("ModifyFrequency 123456789"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_modify_frequency_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_modify_frequency_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_FREQ)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.MODIFY_FREQ
            + " 123456789".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_modify_frequency_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_modify_frequency_sent(message)

    ## error: incorrect number of parameters signed
    #
    def test_modify_frequency_signed_two_param(self):

        utility.issue(utility.generate_signed("ModifyFrequency 123456789 123456789"))
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
    def test_modify_frequency_signed_invalid_param(self):

        utility.issue(utility.generate_signed("ModifyFrequency test"))
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
    def test_modify_frequency_signed_missing_param(self):

        utility.issue(utility.generate_signed("ModifyFrequency"))
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
    def test_modify_frequency_signed_short_param(self):

        utility.issue(utility.generate_signed("ModifyFrequency 12345678"))
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
    def test_modify_frequency_signed_long_param(self):

        utility.issue(utility.generate_signed("ModifyFrequency 1234567890"))
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
