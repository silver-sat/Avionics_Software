##
# @file test_z_local_command_responses.py
# @brief FlatSat test Avionics Board local command responses
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 5 Feb 2023

"""FlatSat test Avionics Board local command responses"""

import utility

## Test local command responses
#
class TestLocalResponses:
    """Test local command responses"""

    ## beacon command
    #
    def test_beacon(self):

        utility.respond(utility.BEACON)

    ## manual antenna release command
    #
    def test_manual_antenna(self):

        utility.respond(utility.MANUAL_RELEASE)

    ## status command
    #
    def test_status(self):

        utility.respond(utility.STATUS)

    ## halt command
    #
    def test_halt(self):

        utility.respond(utility.HALT)

    ## modify frequency command
    #
    def test_modify_frequency(self):

        utility.respond(utility.MODIFY_FREQ)

    ## manual antenna release command
    #
    def test_modify_mode(self):

        utility.respond(utility.MODIFY_MODE)

    ## adjust frequency command
    #
    def test_adjust_frequency(self):

        utility.respond(utility.ADJUST_FREQ)

    ## transmit carrier wave command
    #
    def test_transmit_cw(self):

        utility.respond(utility.TRANSMIT_CARRIER)

    ## background rssi command
    #
    def test_background_rssi(self):

        utility.respond(utility.BACKGROUND_RSSI)

    ## current rssi command
    #
    def test_current_rssi(self):

        utility.respond(utility.CURRENT_RSSI)

    ## sweep transmitter command
    #
    def test_sweep_transmitter(self):

        utility.respond(utility.SWEEP_TRANSMITTER)

    ## sweep receiver command
    #
    def test_sweep_receiver(self):

        utility.respond(utility.SWEEP_RECEIVER)

    ## query register command
    #
    def test_query_register(self):

        utility.respond(utility.QUERY_REGISTER)
