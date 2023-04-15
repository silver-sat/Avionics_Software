##
# @file test_local_command_responses.py
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

        utility.respond(utility.ACK.encode("utf-8") + utility.BEACON)
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)

    ## digital IO antenna release command
    #
    def test_digitalIO_antenna(self):

        # todo: test for two deploy modes
        utility.respond(utility.ACK.encode("utf-8") + utility.DIGITALIO_RELEASE)
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)

    ## status command
    #
    def test_status(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.STATUS)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.STATUS
            + "radio status".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "GRS")
    
    ## status command with leading blank
    #
    def test_status_blank(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.STATUS)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.STATUS
            + " radio status".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "GRS")
    
    ## status command with two leading blanks
    #
    def test_status_two_blanks(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.STATUS)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.STATUS
            + "  radio status".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "GRS")

    ## halt command
    #
    def test_halt(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.HALT)
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)

    ## modify frequency command
    #
    def test_modify_frequency(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_FREQ)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.MODIFY_FREQ
            + "123456789".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RMF")
   
    ## modify frequency command with leading blank
    #
    def test_modify_frequency_blank(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_FREQ)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.MODIFY_FREQ
            + " 123456789".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RMF")
   
    ## modify frequency command with two leading blanks
    #
    def test_modify_frequency_two_blanks(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_FREQ)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.MODIFY_FREQ
            + "  123456789".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RMF")

    ## modify mode command
    #
    def test_modify_mode(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_MODE)
        utility.respond(
            utility.RES.encode("utf-8") + utility.MODIFY_MODE + "1".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RMM")

    ## modify mode command with leading blank
    #
    def test_modify_mode_blank(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_MODE)
        utility.respond(
            utility.RES.encode("utf-8") + utility.MODIFY_MODE + " 1".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RMM")

    ## modify mode command with two leading blanks
    #
    def test_modify_mode_two_blanks(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.MODIFY_MODE)
        utility.respond(
            utility.RES.encode("utf-8") + utility.MODIFY_MODE + "  1".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RMM")

    ## adjust frequency command
    #
    def test_adjust_frequency(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.ADJUST_FREQ)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.ADJUST_FREQ
            + "123456789".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RAF")

    ## adjust frequency command with leading blank
    #
    def test_adjust_frequency_blank(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.ADJUST_FREQ)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.ADJUST_FREQ
            + " 123456789".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RAF")

    ## adjust frequency command with two leading blanks
    #
    def test_adjust_frequency_two_blanks(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.ADJUST_FREQ)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.ADJUST_FREQ
            + "  123456789".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RAF")

    ## transmit carrier wave command
    #
    def test_transmit_cw(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.TRANSMIT_CARRIER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.TRANSMIT_CARRIER
            + "CW mode complete".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RTC")

    ## transmit carrier wave command with leading blank
    #
    def test_transmit_cw_blank(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.TRANSMIT_CARRIER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.TRANSMIT_CARRIER
            + " CW mode complete".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RTC")

    ## transmit carrier wave command with two leading blanks
    #
    def test_transmit_cw_two_blanks(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.TRANSMIT_CARRIER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.TRANSMIT_CARRIER
            + "  CW mode complete".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RTC")

    ## background rssi command
    #
    def test_background_rssi(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.BACKGROUND_RSSI)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.BACKGROUND_RSSI
            + "123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RBR")

    ## background rssi command with leading blank
    #
    def test_background_rssi_blank(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.BACKGROUND_RSSI)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.BACKGROUND_RSSI
            + " 123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RBR")

    ## background rssi command with two leading blanks
    #
    def test_background_rssi_two_blanks(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.BACKGROUND_RSSI)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.BACKGROUND_RSSI
            + "  123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RBR")

    ## current rssi command
    #
    def test_current_rssi(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.CURRENT_RSSI)
        utility.respond(
            utility.RES.encode("utf-8") + utility.CURRENT_RSSI + "123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RCR")

    ## current rssi command with leading blank
    #
    def test_current_rssi_blank(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.CURRENT_RSSI)
        utility.respond(
            utility.RES.encode("utf-8") + utility.CURRENT_RSSI + " 123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RCR")

    ## current rssi command with two leading blanks
    #
    def test_current_rssi_two_blanks(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.CURRENT_RSSI)
        utility.respond(
            utility.RES.encode("utf-8") + utility.CURRENT_RSSI + "  123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RCR")

    ## sweep transmitter command
    #
    def test_sweep_transmitter(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_TRANSMITTER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_TRANSMITTER
            + "sweep done".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RST")

    ## sweep transmitter command with leading blank
    #
    def test_sweep_transmitter_blank(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_TRANSMITTER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_TRANSMITTER
            + " sweep done".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RST")

    ## sweep transmitter command with two leading blanks
    #
    def test_sweep_transmitter_two_blanks(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_TRANSMITTER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_TRANSMITTER
            + "  sweep done".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RST")

    ## sweep receiver command
    #
    def test_sweep_receiver(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_RECEIVER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "123 123456789 123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RSR")

    ## sweep receiver command with leading blank
    #
    def test_sweep_receiver_blank(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_RECEIVER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + " 123 123456789 123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RSR")

    ## sweep receiver command with two leading blanks
    #
    def test_sweep_receiver_two_blanks(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.SWEEP_RECEIVER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.SWEEP_RECEIVER
            + "  123 123456789 123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RSR")

    ## query register command
    #
    def test_query_register(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.QUERY_REGISTER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.QUERY_REGISTER
            + "123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RQR")

    ## query register command with leading blank
    #
    def test_query_register_blank(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.QUERY_REGISTER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.QUERY_REGISTER
            + " 123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RQR")

    ## query register command with two leading blanks
    #
    def test_query_register_two_blanks(self):

        utility.respond(utility.ACK.encode("utf-8") + utility.QUERY_REGISTER)
        utility.respond(
            utility.RES.encode("utf-8")
            + utility.QUERY_REGISTER
            + "  123".encode("utf-8")
        )
        # check log
        log = utility.collect_ack_or_nack()
        assert utility.local_message_received(log)
        assert utility.ack_or_nack_ignored(log)
        # check messages
        message = utility.collect_message()
        assert utility.response_sent(message, "RQR")
