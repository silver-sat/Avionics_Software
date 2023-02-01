##
# @file test_multiple_FENDs.py
# @brief FlatSat test Avionics Board multiple FENDs
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 October 2022

"""FlatSat test Avionics Board multiples FENDs"""

import helper
import serial

## Test incomplete commands
#


class TestMultipleFENDs:
    """Test Multiple FENDs"""

    ## single FEND followed by complete command
    #
    def test_single_FEND(self):
        helper.send_FEND(1)
        message = helper.collect("NoOperate")
        assert helper.acknowledged(message)
        assert helper.executed(message)

    ## two FENDs followed by complete command
    #
    def test_two_FENDs(self):
        helper.send_FEND(2)
        message = helper.collect("NoOperate")
        assert helper.acknowledged(message)
        assert helper.executed(message)

    ## three FENDs followed by complete command
    #
    def test_three_FENDs(self):
        helper.send_FEND(3)
        message = helper.collect("NoOperate")
        assert helper.acknowledged(message)
        assert helper.executed(message)

    ## five FENDs followed by complete command
    #
    def test_five_FENDs(self):
        helper.send_FEND(5)
        message = helper.collect("NoOperate")
        assert helper.acknowledged(message)
        assert helper.executed(message)
