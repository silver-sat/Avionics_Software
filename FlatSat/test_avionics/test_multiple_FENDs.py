##
# @file test_multiple_FENDs.py
# @brief FlatSat test Avionics Board multiple FENDs
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 October 2022

"""FlatSat test Avionics Board multiples FENDs"""

import utility
import serial

## Test incomplete commands
#
class TestMultipleFENDs:
    """Test Multiple FENDs"""

    ## single FEND followed by complete command
    #
    def test_single_FEND(self):

        utility.send_FEND(1)
        utility.issue("NoOperate")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "NOP")

    ## two FENDs followed by complete command
    #
    def test_two_FENDs(self):

        utility.send_FEND(2)
        utility.issue("NoOperate")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "NOP")

    ## three FENDs followed by complete command
    #
    def test_three_FENDs(self):

        utility.send_FEND(3)
        utility.issue("NoOperate")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "NOP")

    ## five FENDs followed by complete command
    #
    def test_five_FENDs(self):

        utility.send_FEND(5)
        utility.issue("NoOperate")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "NOP")
