##
# @file test_send_test_packet.py
# @brief FlatSat test Avionics Board SendTestPacket command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board SendTestPacket command"""

import helper
import serial

## Test SendTestPacket command
#


class TestSendTestPacket:
    """Test SendTestPacket command"""

    ## send test packet
    #
    def test_send_test_packet(self):

        helper.issue("SendTestPacket")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message)