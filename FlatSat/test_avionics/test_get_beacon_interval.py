##
# @file test_get_beacon_interval.py
# @brief FlatSat test Avionics Board GetBeaconInterval command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board GetBeaconInterval command"""

import utility

## Test GetBeaconInterval command
#
class TestGetBeaconInterval:
    """Test GetBeaconInterval command"""

    ## get beacon interval
    #
    def test_get_beacon_interval(self):
        
        utility.issue("GetBeaconInterval")
         # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "GBI")

    ## error: invalid parameter
    #
    def test_get_beacon_interval_param(self):
        
        utility.issue("GetBeaconInterval test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## get beacon interval signed
    #
    def test_get_beacon_interval_signed(self):

        utility.issue(utility.generate_signed("GetBeaconInterval"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.integer_sent_GBI(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "GBI")

    ## error: invalid parameter signed
    #
    def test_get_beacon_interval_param_signed(self):

        utility.issue(utility.generate_signed("GetBeaconInterval test"))
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
