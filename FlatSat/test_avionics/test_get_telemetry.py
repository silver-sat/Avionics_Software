##
# @file test_get_telemetry.py
# @brief FlatSat test Avionics Board GetTelemetry command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board GetTelemetry command"""

import utility

## Test GetTelemetry command
#
class TestGetTelemetry:
    """Test GetTelemetry command"""

    ## get inertial telemetry
    #
    def test_get_telemetry(self):

        utility.issue("GetTelemetry")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.telemetry_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "GTY")

    ## error: invalid parameter
    #
    def test_get_telemetry_param(self):

        utility.issue("GetTelemetry test")
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)


    ## get inertial telemetry signed
    #
    def test_get_telemetry_signed(self):

        utility.issue(utility.generate_signed("GetTelemetry"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.telemetry_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "GTY")


    ## error: invalid parameter signed
    #
    def test_get_telemetry_param_signed(self):

        utility.issue(utility.generate_signed("GetTelemetry test"))
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

