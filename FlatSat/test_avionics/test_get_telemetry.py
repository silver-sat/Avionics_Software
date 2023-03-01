##
# @file test_get_telemetry.py
# @brief FlatSat test Avionics Board GetTelemetry command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board GetTelemetry command"""

import helper

## Test GetTelemetry command
#


class TestGetTelemetry:
    """Test GetTelemetry command"""

    ## get inertial telemetry
    #
    def test_get_telemetry(self):

        helper.issue("GetTelemetry")
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "GTY")