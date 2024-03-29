##
# @file test_unknown.py
# @brief Unit test Avionics Board Unknown command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 20 August 2022

"""Unit test Avionics Board Unknown command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test Unknown command
#


class TestNoOperate:
    """Test NoOperate command"""

    ## unknown command
    #
    def test_unknown(self):

        log = helper.collect("Unknown")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameter
    #
    def test_unknown_param(self):

        log = helper.collect("Unknown test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: command name
    #
    def test_unknown_get_random(self):
        log = helper.collect("GetRandom")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: command name and invalid parameter
    #
    def test_unknown_get_random_param(self):
        log = helper.collect("GetRandom test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## unknown command signed
    #
    def test_unknown_signed(self):

        log = helper.collect(helper.generate_signed("Unknown"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameter signed
    #
    def test_unknown_param_signed(self):

        log = helper.collect(helper.generate_signed("Unknown test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: command name signed
    #
    def test_unknown_get_random_signed(self):
        log = helper.collect(helper.generate_signed("GetRandom"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: command name and invalid parameter signed
    #
    def test_unknown_get_random_param_signed(self):
        log = helper.collect(helper.generate_signed("GetRandom test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
