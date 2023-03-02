##
# @file test_clear_pic_times.py
# @brief FlatSat test Avionics Board ClearPicTimes command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 2 October 2022

"""FlatSat test Avionics Board ClearPicTimes command"""

import utility

## Test ClearPicTimes command
#
class TestClearPicTimes:
    """Test ClearPicTimes command"""

    ## clear picture times
    #
    def test_clear_pic_times(self):

        utility.issue("PicTimes 2025 11 11 10 10 0")
        utility.collect_log()
        utility.discard_messages()

        utility.issue("ClearPicTimes")
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
        assert utility.response_sent(message, "CPT")
        # check picture queue
        utility.issue("GetPicTimes")
        log = utility.collect_log()
        assert utility.pictimes_zero_sent(log)
        # discard messages
        utility.discard_messages()

    ## error: invalid parameter
    #
    def test_clear_pic_times_param(self):

        utility.issue("ClearPicTimes test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## clear picture times signed
    #
    def test_clear_pic_times_signed(self):

        utility.issue("PicTimes 2023 11 11 10 10 0")
        utility.collect_log()
        utility.discard_messages()

        utility.issue(utility.generate_signed("ClearPicTimes"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "CPT")
        # check picture queue
        utility.issue("GetPicTimes")
        log = utility.collect()
        assert utility.pictimes_zero_sent(log)
        # discard messages
        utility.discard_messages()

    ## error: invalid parameter signed
    #
    def test_clear_pic_times_param_signed(self):

        utility.issue(utility.generate_signed("ClearPicTimes test"))
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
