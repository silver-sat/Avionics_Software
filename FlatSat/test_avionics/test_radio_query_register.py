##
# @file test_radio_query_register.py
# @brief FlatSat test Avionics Board QueryRegister command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board QueryRegister command"""

import utility

## Test QueryRegister command
#
class TestQueryRegister:
    """Test QueryRegister command"""

    ## query radio register
    #

    def test_query_register(self):

        utility.issue("QueryRegister 12345")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_query_register_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_query_register_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.QUERY_REGISTER)
        utility.respond(
            utility.RES.encode("utf-8") + utility.QUERY_REGISTER + "123".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_query_register_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_query_register_sent(message)

    ## error: incorrect number of parameters
    #
    def test_query_register_two_param(self):

        utility.issue("QueryRegister 12345 12345")
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
    def test_query_register_invalid_param(self):

        utility.issue("QueryRegister test")
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
    def test_query_register_missing_param(self):

        utility.issue("QueryRegister")
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
    def test_query_register_short_param(self):

        utility.issue("QueryRegister 1234")
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
    def test_query_register_long_param(self):

        utility.issue("QueryRegister 123456")
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
    def test_query_register_signed(self):

        utility.issue(utility.generate_signed("QueryRegister 12345"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.log_local_query_register_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.message_local_query_register_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.QUERY_REGISTER)
        utility.respond(
            utility.RES.encode("utf-8") + utility.QUERY_REGISTER + "123".encode("utf-8")
        )
        # check log
        log = utility.collect_log_radio_response()
        assert utility.log_remote_query_register_sent(log)
        # check messages
        message = utility.collect_message()
        assert utility.message_remote_query_register_sent(message)

    ## error: incorrect number of parameters signed
    #
    def test_query_register_signed_two_param(self):

        utility.issue(utility.generate_signed("QueryRegister 12345 12345"))
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
    def test_query_register_signed_invalid_param(self):

        utility.issue(utility.generate_signed("QueryRegister test"))
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
    def test_query_register_signed_missing_param(self):

        utility.issue(utility.generate_signed("QueryRegister"))
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
    def test_query_register_signed_short_param(self):

        utility.issue(utility.generate_signed("QueryRegister 1234"))
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
    def test_query_register_signed_long_param(self):

        utility.issue(utility.generate_signed("QueryRegister 123456"))
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
