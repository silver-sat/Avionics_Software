##
# @file test_send_test_packet.py
# @brief Unit test Avionics Board SendTestPacket command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.1.0
# @date 22 August 2022

"""Unit test Avionics Board SendTestPacket command"""

import helper
import serial
from collections import namedtuple

## log entry field names
Entry = namedtuple("Entry", ["timestamp", "level", "detail"])

## Test SendTestPacket command
#


class TestSendTestPacket:
    """Test SendTestPacket command"""

    ## send test packet
    #
    def test_send_test_packet(self):

        log = helper.collect("SendTestPacket")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.test_packet_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter
    #
    def test_send_test_packet_param(self):
        log = helper.collect("SendTestPacket test")
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## send test packet signed
    #
    def test_send_test_packet_signed(self):

        log = helper.collect(helper.generate_signed("SendTestPacket"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.test_packet_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter signed
    #
    def test_send_test_packet_param_signed(self):
        log = helper.collect(helper.generate_signed("SendTestPacket test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)
