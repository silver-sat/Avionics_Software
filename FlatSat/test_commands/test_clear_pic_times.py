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

        helper.issue("ClearPicTimes")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message, "CPT")

    ## clear picture times signed
    #
    def test_clear_pic_times_signed(self):

        helper.issue(helper.generate_signed("ClearPicTimes"))
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message, "CPT")
