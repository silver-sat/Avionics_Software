##
# @file test_set_pic_times.py
# @brief FlatSat test Avionics Board PicTimes command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 20 August 2022

"""FlatSat test Avionics Board PicTimes command"""

import utility
import time

## Test PicTimes command
#
class TestPicTimes:
    """Test PicTimes command"""

    ## set picture times
    #
    def test_pic_times(self):

        start_time = time.gmtime(time.time() + 10)
        start_time = time.strftime("%Y %m %d %H %M %S", start_time)
        # check log
        log = utility.collect_through_power_off(f"PicTimes {start_time}")
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        assert utility.payload_power_off(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SPT")
        utility.discard_messages()

    ## error: incorrect number of parameters
    #
    def test_pic_times_no_param(self):

        utility.issue("PicTimes")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: incorrect number of parameters
    #
    def test_pic_times_three_param(self):

        utility.issue("PicTimes 2023 12 12")
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
    def test_pic_times_six_param_invalid(self):

        utility.issue("PicTimes test1 test2 test3 test4 test5 test6")
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
    def test_pic_times_six_zeros(self):

        utility.issue("PicTimes 0 0 0 0 0 0")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: date too early
    #
    def test_pic_times_time_too_early(self):

        utility.issue("PicTimes 2020 10 10 10 10 10")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: date too late
    #
    def test_pic_times_time_too_late(self):

        utility.issue("PicTimes 2100 3 4 5 6 7")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## set picture times signed
    #
    def test_pic_times_signed(self):

        start_time = time.gmtime(time.time() + 10)
        start_time = time.strftime("%Y %m %d %H %M %S", start_time)
        # check log
        log = utility.collect_through_power_off(
            utility.generate_signed(f"PicTimes {start_time}")
        )
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        assert utility.payload_power_off(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SPT")
        utility.discard_messages()

    ## error: no parameters signed
    #
    def test_pic_times_no_param_signed(self):

        utility.issue(utility.generate_signed("PicTimes"))
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

    ## error: three parameters signed
    #
    def test_pic_times_three_param_signed(self):

        utility.issue(utility.generate_signed("PicTimes 2023 12 12"))
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
    def test_pic_times_six_param_invalid_signed(self):

        utility.issue(
            utility.generate_signed("PicTimes test1 test2 test3 test4 test5 test6")
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

    ## error: invalid parameters signed
    #
    def test_pic_times_six_zeros_signed(self):

        utility.issue(utility.generate_signed("PicTimes 0 0 0 0 0 0"))
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

    ## error: date too early signed
    #
    def test_pic_times_time_too_early_signed(self):

        utility.issue(utility.generate_signed("PicTimes 2020 10 10 10 10 10"))
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

    ## error: date too late signed
    #
    def test_pic_times_time_too_late_signed(self):

        utility.issue(utility.generate_signed("PicTimes 2100 3 4 5 6 7"))
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
