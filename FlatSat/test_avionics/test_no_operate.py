##
# @file test_no_operate.py
# @brief FlatSat test Avionics Board NoOperate command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 20 August 2022

"""FlatSat test Avionics Board NoOperate command"""

import utility

## Test NoOperate command
#
class TestNoOperate:
    """Test NoOperate command"""

    ## no operation
    #
    def test_no_operate(self):

        utility.issue("NoOperate")
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
        assert utility.response_sent(message, "NOP")

    ## error: invalid parameter
    #
    def test_no_operate_param(self):

        utility.issue("NoOperate test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: invalid parameters
    #
    def test_no_operate_six_param(self):

        utility.issue("NoOperate test1 test2 test3 test4 test5 test6")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## no operation signed
    #
    def test_no_operate_signed(self):

        utility.issue(utility.generate_signed("NoOperate"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "NOP")

    ## error: invalid parameter signed
    #
    def test_no_operate_param_signed(self):

        utility.issue(utility.generate_signed("NoOperate test"))
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

    ## error: invalid parameters signed
    #
    def test_no_operate_six_param_signed(self):

        utility.issue(
            utility.generate_signed("NoOperate test1 test2 test3 test4 test5 test6")
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
