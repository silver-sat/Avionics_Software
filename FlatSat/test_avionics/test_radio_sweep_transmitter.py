##
# @file test_radio_sweep_transmitter.py
# @brief FlatSat test Avionics Board SweepTransmitter command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 7 February 2023

"""FlatSat test Avionics Board SweepTransmitter command"""

import utility

## Test SweepTransmitter command
#


class TestSweepTransmitter:
    """Test SweepTransmitter command"""

    ## sweep transmitter
    #
    def test_sweep_transmitter(self):

        utility.issue("SweepTransmitter 123456789 123456789 123 123")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect - MemoryError()
        assert utility.local_sweep_transmitter_message_sent(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_TRANSMITTER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_TRANSMITTER
            + "sweep done".encode("utf-8")
        )
        message = utility.collect_message()
        assert utility.response_sent(message, "RST")
