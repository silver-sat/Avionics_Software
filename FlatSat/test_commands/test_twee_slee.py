##
# @file test_twee_slee.py
# @brief FlatSat test Avionics Board TweeSlee command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 20 August 2022

"""FlatSat test Avionics Board TweeSlee command"""

import helper

## Test TweeSlee command
#


class TestTweeSlee:
    """Test TweeSlee command"""

    ## test active payload to sleep
    #
    def test_twee_slee(self):

        helper.issue("TweeSlee")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message, "TSL")
        message = helper.collect()
        assert helper.local_halt_message_sent(message)

