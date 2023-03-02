##
# @file test_get_power.py
# @brief FlatSat test Avionics Board GetPower command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board GetPower command"""

import utility

## Test GetPower command
#
class TestGetPower:
    """Test GetPower command"""

    ## get power information
    #
    def test_get_power(self):

        utility.issue("GetPower")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.power_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "GPW")

    ## error: invalid parameter
    #
    def test_get_power_param(self):

        utility.issue("GetPower test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## get power information signed
    #
    def test_get_power_signed(self):

        utility.issue(utility.generate_signed("GetPower"))
        # check log
        log = utility.collect()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged(log)
        assert utility.no_logged_errors(log)
        assert utility.power_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "GPW")

    ## error: invalid parameter signed
    #
    def test_get_power_param_signed(self):

        utility.issue(utility.generate_signed("GetPower test"))
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
