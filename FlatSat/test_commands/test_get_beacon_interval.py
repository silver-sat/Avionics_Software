##
# @file test_get_beacon_interval.py
# @brief FlatSat test Avionics Board GetBeaconInterval command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board GetBeaconInterval command"""

import helper

## Test GetBeaconInterval command
#


class TestGetBeaconInterval:
    """Test GetBeaconInterval command"""

    ## get beacon interval
    #
    def test_get_beacon_interval(self):

        helper.issue("GetBeaconInterval")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message)