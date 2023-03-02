##
# @file test_get_pic_times.py
# @brief FlatSat test Avionics Board GetPicTimes command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board GetPicTimes command"""

import utility

## Test GetPicTimes command
#
class TestGetPicTimes:
    """Test GetPicTimes command"""

    ## get picture times
    #
    def test_get_pic_times(self):

        utility.issue("PicTimes 2025 11 11 10 10 0")
        utility.collect_log()
        utility.discard_messages()

        utility.issue("GetPicTimes")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged(log)
        assert utility.no_logged_errors(log)
        assert utility.pictimes_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "GPT")

    ## error: invalid parameter
    #
    def test_get_pic_times_param(self):

        utility.issue("GetPicTimes test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## get picture times signed
    #
    def test_get_pic_times_signed(self):

        utility.issue("PicTimes 2025 11 11 10 10 0")
        utility.collect_log()
        utility.discard_messages()

        utility.issue(utility.generate_signed("GetPicTimes"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged(log)
        assert utility.no_logged_errors(log)
        assert utility.pictimes_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "GPT")

    ## error: invalid parameter signed
    #
    def test_get_pic_times_param_signed(self):

        utility.issue(utility.generate_signed("GetPicTimes test"))
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
