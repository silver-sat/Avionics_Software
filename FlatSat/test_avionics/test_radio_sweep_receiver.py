##
# @file test_radio_sweep_receiver.py
# @brief FlatSat test Avionics Board SweepReceiver command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 7 February 2023

"""FlatSat test Avionics Board SweepReceiver command"""

import utility

## Test SweepReceiver command
#


class TestSweepReceiver:
    """Test SweepReceiver command"""

    ## sweep receiver
    #
    def test_sweep_receiver(self):

        utility.issue("SweepReceiver 123456789 123456789 123 123")
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
        assert utility.local_sweep_receiver_message_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_RECEIVER)
        utility.respond(utility.RES.encode("utf-8") + utility.SWEEP_RECEIVER + "123123456789123".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RSR")
        utility.respond(utility.RES.encode("utf-8") + utility.SWEEP_RECEIVER + "123123456789123".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RSR")
        utility.respond(utility.RES.encode("utf-8") + utility.SWEEP_RECEIVER + "123123456789123".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RSR")
        utility.respond(utility.RES.encode("utf-8") + utility.SWEEP_RECEIVER + "123123456789123".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RSR")
        utility.respond(utility.RES.encode("utf-8") + utility.SWEEP_RECEIVER + "123123456789123".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "RSR")
