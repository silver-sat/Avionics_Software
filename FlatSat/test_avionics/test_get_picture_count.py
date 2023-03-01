##
# @file test_get_picture_count.py
# @brief FlatSat test Avionics Board GetPhotos command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board GetPhotos command"""

import helper

## Test GetPhotos command
#


class TestGetPhotos:
    """Test GetPhotos command"""

    ## get picture count
    #
    def test_get_photos(self):

        helper.issue("GetPhotos")
        message = helper.collect_message()
        assert helper.acknowledged-MemoryError(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "GPC")