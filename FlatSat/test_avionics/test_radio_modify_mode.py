##
# @file test_radio_modify_mode.py
# @brief FlatSat test Avionics Board ModifyMode command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board ModifyMode command"""

import utility

## Test ModifyMode command
#
class TestModifyMode:
    """Test ModifyMode command"""

    ## modify mode
    #
    def test_modify_mode(self):

        utility.issue("ModifyMode 1")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_modify_mode_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_modify_mode_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_MODE)
        utility.respond(
            utility.RES.encode("utf-8") + utility.MODIFY_MODE + " 1".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_modify_mode_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_modify_mode_sent(message)

    ## error: incorrect number of parameters
    #
    def test_modify_mode_two_param(self):

        utility.issue("ModifyMode 1 1")
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
    def test_modify_mode_invalid_param(self):

        utility.issue("ModifyMode test")
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
    def test_modify_mode_missing_param(self):

        utility.issue("ModifyMode")
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
    def test_modify_mode_long_param(self):

        utility.issue("ModifyMode 12")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## modify mode signed
    #
    def test_modify_mode_signed(self):

        utility.issue(utility.generate_signed("ModifyMode 1"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_modify_mode_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_modify_mode_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_MODE)
        utility.respond(
            utility.RES.encode("utf-8") + utility.MODIFY_MODE + " 1".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_modify_mode_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_modify_mode_sent(message)

    ## error: incorrect number of parameters signed
    #
    def test_modify_mode_signed_two_param(self):

        utility.issue(utility.generate_signed("ModifyMode 1 1"))
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
    def test_modify_mode_signed_invalid_param(self):

        utility.issue(utility.generate_signed("ModifyMode test"))
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
    def test_modify_mode_signed_missing_param(self):

        utility.issue(utility.generate_signed("ModifyMode"))
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
    def test_modify_mode_signed_long_param(self):

        utility.issue(utility.generate_signed("ModifyMode 12"))
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
