##
# @file test_no_operate.py
# @brief Unit test Avionics Board NoOperate command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 20 August 2022

"""Unit test Avionics Board NoOperate command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test NoOperate command
#


class TestNoOperate:
    """Test NoOperate command"""

    ## no operation
    #
    def test_no_operate(self):

        log = helper.collect("NoOperate")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## error: invalid parameter
    #
    def test_no_operate_param(self):
        log = helper.collect("NoOperate test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters
    #
    def test_no_operate_six_param(self):
        log = helper.collect("NoOperate test1 test2 test3 test4 test5 test6")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## no operation signed
    #
    def test_no_operate_signed(self):

        log = helper.collect(helper.generate_signed("NoOperate"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)

    ## error: invalid parameter signed
    #
    def test_no_operate_param_signed(self):
        log = helper.collect(helper.generate_signed("NoOperate test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## error: invalid parameters signed
    #
    def test_no_operate_six_param_signed(self):
        log = helper.collect(helper.generate_signed("NoOperate test1 test2 test3 test4 test5 test6"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
