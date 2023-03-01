##
# @file test_get_realtime_clock.py
# @brief FlatSat test Avionics Board ReportT command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board ReportT command"""

import helper

## Test ReportT command
#


class TestReportT:
    """Test ReportT command"""

    ## get realtime clock time
    #
    def test_report_t(self):

        helper.issue("ReportT")
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "GRC")
