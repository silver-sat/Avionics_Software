##
# @file test_get_comms_status.py
# @brief FlatSat test Avionics Board GetComms command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 22 August 2022

"""FlatSat test Avionics Board GetComms command"""

import utility

## Test GetComms command
#
class TestGetComms:
    """Test GetComms command"""

    ## get communications status
    #
    def test_get_comms(self):

        utility.issue("GetComms")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.local_get_comms_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.local_status_request(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.STATUS)
        utility.respond(utility.RES.encode("utf-8") + utility.STATUS + "Radio Status".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "GRS")

    ## error: invalid parameter
    #
    def test_get_comms_param(self):

        utility.issue("GetComms test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## get communications status signed
    #
    def test_get_comms_signed(self):

        utility.issue(utility.generate_signed("GetComms"));
        # check log                                  
        log = utility.collect_log();
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.local_get_comms_sent(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.local_status_request(message)
        utility.respond(utility.ACK.encode("utf-8") + utility.STATUS)
        utility.respond(utility.RES.encode("utf-8") + utility.STATUS + "Radio Status".encode("utf-8"))
        message = utility.collect_message()
        assert utility.response_sent(message, "GRS")

    ## error: invalid parameter signed
    #
    def test_get_comms_param_signed(self):
        
        utility.issue(utility.generate_signed("GetComms test"))
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

