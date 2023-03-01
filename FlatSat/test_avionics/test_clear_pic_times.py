##
# @file test_clear_pic_times.py
# @brief FlatSat test Avionics Board ClearPicTimes command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 2 October 2022

"""FlatSat test Avionics Board ClearPicTimes command"""

import helper

## Test ClearPicTimes command
#


class TestClearPicTimes:
    """Test ClearPicTimes command"""
     

 ## clear picture times
    #
    def test_clear_pic_times(self):

        helper.issue("PicTimes 2025 11 11 10 10 0")
        helper.collect_log()
        helper.collect_message()
        helper.collect_message()
        # helper.discard_messages()
        helper.issue("ClearPicTimes")
        # check log
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "CPT")
        # check picture queue
        log = helper.collect("GetPicTimes")
        assert helper.pictimes_zero_sent(log)
        # discard messages
        helper.discard_messages()

    ## error: invalid parameter
    #
    def test_clear_pic_times_param(self):

        helper.issue("ClearPicTimes test")
        # check logs
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.negative_acknowledged_log(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)

    ## clear picture times signed
    #
    def test_clear_pic_times_signed(self):

        helper.issue("PicTimes 2023 11 11 10 10 0")
        helper.discard_messages()
        helper.issue(helper.generate_signed("ClearPicTimes"))
        # check log
        log = helper.collect_log()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check messages 
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "CPT")
        # check picture queue
        helper.issue("GetPicTimes")
        log = helper.collect()
        assert helper.pictimes_zero_sent(log)
        # discard messages
        helper.discard_messages()

    ## error: invalid parameter signed
    #
    def test_clear_pic_times_param_signed(self):

        helper.issue(helper.generate_signed("ClearPicTimes test"))
        # check log
        log = helper.collect_log()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.negative_acknowledged_log(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)
