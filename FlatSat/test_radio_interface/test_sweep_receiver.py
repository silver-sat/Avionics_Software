##
# @file test_sweep_receiver.py
# @brief FlatSat test Avionics Board SweepReceiver command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board SweepReceiver command"""

import helper

## Test SweepReceiver command
#


class TestSweepReceiver:
    """Test SweepReceiver command"""

    ## sweep receiver
    #
    def test_sweep_receiver(self):

        helper.issue("SweepReceiver 123456789 123456789 123 123")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.local_sweep_receiver_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.SWEEP_RECEIVER)
        helper.respond(helper.RES.encode("utf-8") + helper.SWEEP_RECEIVER + "123123456789123".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RSR")
        helper.respond(helper.RES.encode("utf-8") + helper.SWEEP_RECEIVER + "123123456789123".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RSR")
        helper.respond(helper.RES.encode("utf-8") + helper.SWEEP_RECEIVER + "123123456789123".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RSR")
        helper.respond(helper.RES.encode("utf-8") + helper.SWEEP_RECEIVER + "123123456789123".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RSR")
        helper.respond(helper.RES.encode("utf-8") + helper.SWEEP_RECEIVER + "123123456789123".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RSR")
