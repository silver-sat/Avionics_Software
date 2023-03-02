##
# @file test_pay_comms.py
# @brief FlatSat test Avionics Board PayComms command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board PayComms command"""

import utility

## Test PayComms command
#
class TestPayComms:
    """Test PayComms command"""

    ## start payload communications
    #
    def test_pay_comms(self):

        # check log
        log = utility.collect_through_power_off("PayComms")
        assert utility.not_signed(log)
        assert utility.acknowledged(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        assert utility.payload_power_off(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "PYC")

    ## error: invalid parameter
    #
    def test_pay_comms_param(self):

        utility.issue("PayComms test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## start payload communications signed
    #
    def test_pay_comms_signed(self):

        log = utility.collect_through_power_off(utility.generate_signed("PayComms"))
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        assert utility.payload_power_off(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "PYC")

    ## error: invalid parameter signed
    #
    def test_pay_comms_param_signed(self):

        utility.issue(utility.generate_signed("PayComms test"))
        # check log
        log = utility.collect()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)
