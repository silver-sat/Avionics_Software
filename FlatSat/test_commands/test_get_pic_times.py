##
# @file test_get_pic_times.py
# @brief FlatSat test Avionics Board GetPicTimes command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board GetPicTimes command"""

import helper

## Test GetPicTimes command
#


class TestGetPicTimes:
    """Test GetPicTimes command"""

    ## get picture times
    #
    def test_get_pic_times(self):

        helper.issue("GetPicTimes")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message, "GPT")
