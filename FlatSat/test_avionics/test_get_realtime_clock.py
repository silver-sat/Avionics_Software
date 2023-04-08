##
# @file test_get_realtime_clock.py
# @brief FlatSat test Avionics Board ReportT command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board ReportT command"""

import utility

## Test ReportT command
#
class TestReportT:
    """Test ReportT command"""

    ## report realtime clock time
    #
    def test_report_t(self):

        utility.issue("ReportT")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.timestamp_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "GRC")

    ## error: invalid parameter
    #
    def test_report_t_param(self):

        utility.issue("ReportT test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## report realtime clock time signed
    #
    def test_report_t_signed(self):

        utility.issue(utility.generate_signed("ReportT"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.timestamp_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "GRC")

    ## error: invalid parameter signed
    #
    def test_report_t_param_signed(self):

        log = utility.issue(utility.generate_signed("ReportT test"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)
