##
# @file test_set_realtime_clock.py
# @brief FlatSat test Avionics Board SetClock command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board SetClock command"""

import helper
from datetime import datetime
from datetime import timezone

## Test SetClock command
#


class TestSetClock:
    """Test SetClock command"""

    ## set realtime clock with current time
    #
    def test_set_clock(self):

        utc_time = datetime.now(timezone.utc)
        helper.issue("SetClock " + utc_time.strftime("%Y %m %d %H %M %S"))
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SRC")
    
    ## set realtime clock with current time signed
    #
    def test_set_clock(self):

        utc_time = datetime.now(timezone.utc)
        helper.issue(helper.generate_signed("SetClock " + utc_time.strftime("%Y %m %d %H %M %S")))
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "SRC")



