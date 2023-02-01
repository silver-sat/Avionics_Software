##
# @file test_invalid.py
# @brief FlatSat test Avionics Board Invalid command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 20 August 2022

"""FlatSat test Avionics Board Invalid command"""

import helper
import serial

## Test Invalid command
#


class TestInvalid:
    """Test Invalid command"""

    ## invalid command
    #
    def test_invalid(self):

        message = helper.collect("Invalid")
        assert helper.negative_acknowledged(message)

    ## invalid command signed
    #
    def test_invalid_signed(self):

        message = helper.collect(helper.generate_signed("Invalid"))
        assert helper.negative_acknowledged(message)