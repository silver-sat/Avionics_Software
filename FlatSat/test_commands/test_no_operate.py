##
# @file test_no_operate.py
# @brief FlatSat test Avionics Board NoOperate command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 20 August 2022

"""FlatSat test Avionics Board NoOperate command"""

import helper

## Test NoOperate command
#


class TestNoOperate:
    """Test NoOperate command"""

    ## no operation
    #
    def test_no_operate(self):

        helper.issue("NoOperate")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message)