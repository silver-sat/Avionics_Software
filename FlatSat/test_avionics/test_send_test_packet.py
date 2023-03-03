##
# @file test_send_test_packet.py
# @brief FlatSat test Avionics Board SendTestPacket command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board SendTestPacket command"""

import utility

## Test SendTestPacket command
#
class TestSendTestPacket:
    """Test SendTestPacket command"""

    ## send test packet
    #
    def test_send_test_packet(self):

        utility.issue("SendTestPacket")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.test_packet_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "STPTEST")

    ## error: invalid parameter
    #
    def test_send_test_packet_param(self):

        utility.issue("SendTestPacket test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## send test packet signed
    #
    def test_send_test_packet_signed(self):

        utility.issue(utility.generate_signed("SendTestPacket"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.test_packet_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "STPTEST")

    ## error: invalid parameter signed
    #
    def test_send_test_packet_param_signed(self):

        utility.issue(utility.generate_signed("SendTestPacket test"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)
