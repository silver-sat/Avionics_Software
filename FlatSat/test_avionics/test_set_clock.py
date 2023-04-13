##
# @file test_set_clock.py
# @brief FlatSat test Avionics Board SetClock command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.1
# @date 21 August 2022

"""FlatSat test Avionics Board SetClock command"""

import utility
from datetime import datetime
from datetime import timezone

## Test SetClock command
#
class TestSetClock:
    """Test SetClock command"""

    ## set realtime clock
    #
    def test_set_clock_early(self):

        utility.issue("SetClock 2022 1 1 10 10 0")
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
        assert utility.response_sent(message, "SRC")

    ## set realtime clock with current time
    #
    def test_set_clock(self):

        utc_time = datetime.now(timezone.utc)
        utility.issue("SetClock " + utc_time.strftime("%Y %m %d %H %M %S"))
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
        assert utility.response_sent(message, "SRC")

    ## error: incorrect number of parameters
    #
    def test_set_clock_no_param(self):

        utility.issue("SetClock")
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
    def test_set_clock_three_param(self):

        utility.issue("SetClock 2023 12 12")
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
    def test_set_clock_six_param_invalid(self):

        utility.issue("SetClock test1 test2 test3 test4 test5 test6")
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
    def test_set_clock_six_zeros(self):

        utility.issue("SetClock 0 0 0 0 0 0")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.error_response(message)

    ## error: time to early
    #
    def test_set_clock_time_too_early(self):

        utility.issue("SetClock 2020 10 10 10 10 10")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.error_response(message)

    ## error: time too late
    #
    def test_set_clock_time_too_late(self):

        utility.issue("SetClock 2100 3 4 5 6 7")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.error_response(message)

    ## set realtime clock signed
    #
    def test_set_clock_early_signed(self):

        utility.issue(utility.generate_signed("SetClock 2022 1 1 10 10 0"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SRC")

    ## set realtime clock with current time signed
    #
    def test_set_clock_signed(self):

        utc_time = datetime.now(timezone.utc)
        utility.issue(
            utility.generate_signed("SetClock " + utc_time.strftime("%Y %m %d %H %M %S"))
        )
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SRC")

    ## error: incorrect number of parameters signed
    #
    def test_set_clock_no_param_signed(self):

        utility.issue(utility.generate_signed("SetClock"))
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

    ## error: incorrect number of parameters signed
    #
    def test_set_clock_three_param_signed(self):

        utility.issue(utility.generate_signed("SetClock 2023 12 12"))
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
    def test_set_clock_six_param_invalid_signed(self):

        log = utility.issue(
            utility.generate_signed("SetClock test1 test2 test3 test4 test5 test6")
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
    def test_set_clock_six_zeros_signed(self):

        utility.issue(utility.generate_signed("SetClock 0 0 0 0 0 0"))
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
        assert utility.error_response(message)

    ## error: time to early signed
    #
    def test_set_clock_time_too_early_signed(self):

        utility.issue(utility.generate_signed("SetClock 2020 10 10 10 10 10"))
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
        assert utility.error_response(message)

    ## error: time too late
    #
    def test_set_clock_time_too_late_signed(self):

        utility.issue(utility.generate_signed("SetClock 2100 3 4 5 6 7"))
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
        assert utility.error_response(message)
