##
# @file test_invalid.py
# @brief Unit test Avionics Board Invalid command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 20 August 2022

"""Unit test Avionics Board Invalid command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test Invalid command
#


class TestInvalid:
    """Test Invalid command"""

    ## invalid command
    #
    def test_invalid(self):

        log = helper.collect("Invalid")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameter
    #
    def test_invalid_param(self):
        log = helper.collect("Invalid test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters
    #
    def test_invalid_two_param(self):
        log = helper.collect("Invalid test1 test2")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters
    #
    def test_invalid_six_param(self):
        log = helper.collect("Invalid test1 test2 test3 test4 test5 test6")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters
    #
    def test_invalid_seven_param(self):
        log = helper.collect("Invalid test1 test2 test3 test4 test5 test6 test7")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## invalid command signed
    #
    def test_invalid_signed(self):

        log = helper.collect(helper.generate_signed("Invalid"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameter signed
    #
    def test_invalid_param_signed(self):
        log = helper.collect(helper.generate_signed("Invalid test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters signed
    #
    def test_invalid_two_param_signed(self):
        log = helper.collect(helper.generate_signed("Invalid test1 test2"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters signed
    #
    def test_invalid_six_param_signed(self):
        log = helper.collect(helper.generate_signed("Invalid test1 test2 test3 test4 test5 test6"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters signed
    #
    def test_invalid_seven_param_signed(self):
        log = helper.collect(helper.generate_signed("Invalid test1 test2 test3 test4 test5 test6 test7"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
