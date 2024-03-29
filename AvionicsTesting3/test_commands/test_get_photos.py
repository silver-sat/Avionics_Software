##
# @file test_get_photos.py
# @brief Unit test Avionics Board GetPhotos command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 22 August 2022

"""Unit test Avionics Board GetPhotos command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test GetPhotos command
#


class TestGetPhotos:
    """Test GetPhotos command"""

    ## get photo count
    #
    def test_get_photos(self):

        log = helper.collect("GetPhotos")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.integer_sent_GPC(log)
        assert helper.executed(log)

    ## error: invalid parameter
    #
    def test_get_photos_param(self):
        log = helper.collect("GetPhotos test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## get photo count signed
    #
    def test_get_photos_signed(self):

        log = helper.collect(helper.generate_signed("GetPhotos"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.integer_sent_GPC(log)
        assert helper.executed(log)

    ## error: invalid parameter signed
    #
    def test_get_photos_param_signed(self):
        log = helper.collect(helper.generate_signed("GetPhotos test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
