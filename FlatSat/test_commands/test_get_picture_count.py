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
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message)