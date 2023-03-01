##
# @file test_set_pic_times.py
# @brief FlatSat test Avionics Board PicTimes command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 20 August 2022

"""FlatSat test Avionics Board PicTimes command"""

import helper
import time

## Test PicTimes command
#


class TestPicTimes:
    """Test PicTimes command"""

    ## set picture times
    #
    def test_pic_times(self):
        current_time = time.gmtime(time.time())
        current_time = time.strftime("%Y %m %d %H %M %S", current_time)
        helper.issue(f"PicTimes {current_time}")
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SPT")

    ## set picture times signed
    #
    def test_pic_times_signed(self):

        current_time = time.gmtime(time.time())
        current_time = time.strftime("%Y %m %d %H %M %S", current_time)
        helper.issue(helper.generate_signed(f"PicTimes {current_time}"))
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SPT")
