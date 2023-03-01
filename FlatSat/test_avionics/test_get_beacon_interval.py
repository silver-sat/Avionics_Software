##
# @file test_get_beacon_interval.py
# @brief FlatSat test Avionics Board GetBeaconInterval command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board GetBeaconInterval command"""

import helper

## Test GetBeaconInterval command
#


class TestGetBeaconInterval:
    """Test GetBeaconInterval command"""

    ## get beacon interval
    #
    def test_get_beacon_interval(self):
        
        helper.issue("GetBeaconInterval")
         # check log
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.acknowledged_log(log)
        assert helper.no_logged_errors(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "GBI")

    ## error: invalid parameter
    #
    def test_get_beacon_interval_param(self):
        helper.issue("GetBeaconInterval test")
        # check logs
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.negative_acknowledged_log(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)

    ## get beacon interval signed
    #
    def test_get_beacon_interval_signed(self):

        helper.issue(helper.generate_signed("GetBeaconInterval"))
        # check log
        log = helper.collect()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.integer_sent_GBI(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)
        message = helper.collect_message()
        assert helper.response_sent(message, "GBI")

    ## error: invalid parameter signed
    #
    def test_get_beacon_interval_param_signed(self):

        helper.issue(helper.generate_signed("GetBeaconInterval test"))
        # check logs
        log = helper.collect_log()
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.negative_acknowledged_log(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.negative_acknowledged_message(message)
