##
# @file test_get_comms_status.py
# @brief FlatSat test Avionics Board GetComms command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board GetComms command"""

import helper
import serial

## Test GetComms command
#


class TestGetComms:
    """Test GetComms command"""

    ## get communications status
    #
    def test_get_comms(self):

        helper.issue("GetComms")
        # check logs
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.local_get_comms_sent(log)
        assert helper.executed(log)
        # check messages
        message = helper.collect_message()
        assert helper.acknowledged_message(message)
        message = helper.collect_message()
        assert helper.local_status_request(message)
        helper.respond(helper.ACK.encode("utf-8") + helper.STATUS)
        helper.respond(helper.RES.encode("utf-8") + helper.STATUS + "Radio Status".encode("utf-8"))
        message = helper.collect_message()
        assert helper.response_sent(message, "GRS")

    ## error: invalid parameter
    #
    def test_get_comms_param(self):

        helper.issue("GetComms test")
        # check logs
        log = helper.collect_log()
        assert helper.not_signed(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

    ## get communications status signed
    #
    def test_get_comms_signed(self):

        log = helper.collect(helper.generate_signed("GetComms"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert helper.no_logged_errors(log)
        assert helper.local_get_comms_sent(log)
        assert helper.executed(log)

    ## error: invalid parameter signed
    #
    def test_get_comms_param_signed(self):
        log = helper.collect(helper.generate_signed("GetComms test"))
        assert helper.signed(log)
        assert helper.signature_valid(log)
        assert helper.acknowledged(log)
        assert not helper.no_logged_errors(log)
        assert not helper.executed(log)

