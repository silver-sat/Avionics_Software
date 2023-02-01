##
# @file test_get_comms.py
# @brief FlatSat test Avionics Board GetComms command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board GetComms command"""

import helper
import serial

## Test GetComms command
#


class TestGetComms:
    """Test GetComms command"""

    ## get communications status
    #
    def test_get_comms(self):

        helper.issue("GetComms")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.local_status_request(message)
        message = helper.collect()
        assert helper.response_sent(message)
