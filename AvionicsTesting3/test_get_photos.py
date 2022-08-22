##
# @file test_get_photos.py   
# @brief Unit test Avionics Board GetPhotos command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 22 August 2022

"""Unit test Avionics Board GetPhotos command"""

import helper
import serial
from collections import namedtuple
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test GetPhotos command
#

class TestGetPhotos:
    """Test GetPhotos command"""
    
    def test_get_photos(self):

        log = helper.collect("GetPhotos")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.integer_sent(log)
        assert helper.executed(log)

    def test_get_photos_param(self):
        log = helper.collect("GetPhotos test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
