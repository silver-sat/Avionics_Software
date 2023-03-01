##
# @file test_z_local_command_responses.py
# @brief FlatSat test Avionics Board local command responses
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 5 Feb 2023

"""FlatSat test Avionics Board local command responses"""

import helper

## Test local command responses
#


class TestLocalResponses:
    """Test local command responses"""

    ## beacon command
    #
    def test_beacon(self):

        helper.respond(helper.BEACON)

    ## manual antenna release command
    #
    def test_manual_antenna(self):

        helper.respond(helper.MANUAL_RELEASE)

    ## status command
    #
    def test_status(self):

        helper.respond(helper.STATUS)

    ## halt command
    #
    def test_halt(self):

        helper.respond(helper.HALT)

    ## modify frequency command
    #
    def test_modify_frequency(self):

        helper.respond(helper.MODIFY_FREQ)

    ## manual antenna release command
    #
    def test_modify_mode(self):

        helper.respond(helper.MODIFY_MODE)

    ## adjust frequency command
    #
    def test_adjust_frequency(self):

        helper.respond(helper.ADJUST_FREQ)

    ## transmit carrier wave command
    #
    def test_transmit_cw(self):

        helper.respond(helper.TRANSMIT_CARRIER)

    ## background rssi command
    #
    def test_background_rssi(self):

        helper.respond(helper.BACKGROUND_RSSI)

    ## current rssi command
    #
    def test_current_rssi(self):

        helper.respond(helper.CURRENT_RSSI)

    ## sweep transmitter command
    #
    def test_sweep_transmitter(self):

        helper.respond(helper.SWEEP_TRANSMITTER)

    ## sweep receiver command
    #
    def test_sweep_receiver(self):

        helper.respond(helper.SWEEP_RECEIVER)

    ## query register command
    #
    def test_query_register(self):

        helper.respond(helper.QUERY_REGISTER)
