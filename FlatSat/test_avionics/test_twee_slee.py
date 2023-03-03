##
# @file test_twee_slee.py
# @brief FlatSat test Avionics Board TweeSlee command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 20 August 2022

"""FlatSat test Avionics Board TweeSlee command"""

import utility

## Test TweeSlee command
#
class TestTweeSlee:
    """Test TweeSlee command"""

    ## test active payload to sleep
    #
    def test_twee_slee(self):

        utility.issue("TweeSlee")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        assert utility.local_stop_message_sent(log)
        assert utility.payload_power_off(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "TSL")
        message = utility.collect_message()
        assert utility.local_halt_message_sent(message)

    ## error: invalid parameter
    #
    def test_twee_slee_param(self):

        utility.issue("TweeSlee test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)

    ## active payload to sleep signed
    #
    def test_twee_slee_signed(self):

        utility.issue(utility.generate_signed("TweeSlee"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        assert utility.local_stop_message_sent(log)
        assert utility.payload_power_off(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "TSL")
        message = utility.collect_message()
        assert utility.local_halt_message_sent(message)

    ## error: invalid parameter signed
    #
    def test_twee_slee_param_signed(self):

        utility.issue(utility.generate_signed("TweeSlee test"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
