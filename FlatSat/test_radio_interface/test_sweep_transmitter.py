##
# @file test_sweep_transmitter.py
# @brief FlatSat test Avionics Board SweepTransmitter command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 February 2023

"""FlatSat test Avionics Board SweepTransmitter command"""

import helper

## Test SweepTransmitter command
#


class TestSweepTransmitter:
    """Test SweepTransmitter command"""

    ## sweep transmitter
    #
    def test_sweep_transmitter(self):

        helper.issue("SweepTransmitter 123456789 123456789 123 123")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.local_sweep_transmitter_message_sent(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.SWEEP_TRANSMITTER)
        helper.respond(helper.RES.encode("utf-8") + helper.SWEEP_TRANSMITTER + "sweep done".encode("utf-8"))
        message = helper.collect()
        assert helper.response_sent(message, "RST")
