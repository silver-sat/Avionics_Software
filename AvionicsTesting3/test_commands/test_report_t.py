##
# @file test_report_t.py
# @brief Unit test Avionics Board ReportT command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 21 August 2022

"""Unit test Avionics Board ReportT command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test ReportT command
#


class TestReportT:
    """Test ReportT command"""

    ## report realtime clock time
    #
    def test_report_t(self):

        log = helper.collect("ReportT")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.timestamp_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter
    #
    def test_report_t_param(self):
        log = helper.collect("ReportT test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## report realtime clock time signed
    #
    def test_report_t_signed(self):

        log = helper.collect(helper.generate_signed("ReportT"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.timestamp_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter signed
    #
    def test_report_t_param_signed(self):
        log = helper.collect(helper.generate_signed("ReportT test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
