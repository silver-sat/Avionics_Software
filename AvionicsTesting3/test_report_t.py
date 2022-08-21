##
# @file test_report_t.py   
# @brief Unit test Avionics Board ReportT command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 21 August 2022

"""Unit test Avionics Board ReportT command"""

import helper
import serial
from collections import namedtuple
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test ReportT command
#

class TestReportT:
    """Test ReportT command"""
    
    def test_report_t(self):

        log = helper.collect("ReportT")
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.timestamp_sent(log)
        assert helper.executed(log)

    def test_report_t_param(self):
        log = helper.collect("ReportT test")
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
