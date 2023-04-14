##
# @file test_set_beacon_sp.py
# @brief FlatSat test Avionics Board BeaconSp command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.1
# @date 21 August 2022

"""FlatSat test Avionics Board BeaconSp command"""

import utility

## Test BeaconSp command
#
class TestBeaconSp:
    """Test BeaconSp command"""

    ## 60 second spacing
    #
    def test_beacon_sp_60(self):

        interval = 60
        utility.issue(f"BeaconSp {interval}")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")
        # verify beacon interval
        log = utility.collect_two_beacons(interval)
        assert utility.beacon_interval(interval, log)
        # verify beacon messages
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)

    ## 120 second spacing
    #
    def test_beacon_sp_120(self):

        interval = 120
        utility.issue(f"BeaconSp {interval}")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")
        # verify beacon interval
        log = utility.collect_two_beacons(interval)
        assert utility.beacon_interval(interval, log)
        # verify beacon messages
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)

    ## 90 second spacing
    #
    def test_beacon_sp_90(self):

        interval = 90
        utility.issue(f"BeaconSp {interval}")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")
        # verify beacon interval
        log = utility.collect_two_beacons(interval)
        assert utility.beacon_interval(interval, log)
        # verify beacon messages
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)

    ## no beacon
    #
    def test_beacon_sp_0(self):

        interval = 0
        utility.issue(f"BeaconSp {interval}")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")
        # verify no beacons sent
        assert utility.collect_timeout()

    ## error: no parameter
    #
    def test_beacon_sp_no_param(self):

        utility.issue(f"BeaconSp")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: two parameters
    #
    def test_beacon_sp_two_param(self):

        utility.issue("BeaconSp 100 200")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: invalid parameter
    #
    def test_beacon_sp_param_invalid(self):

        utility.issue("BeaconSp test")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: parameter outside range
    #
    def test_beacon_sp_param_range(self):

        utility.issue("BeaconSp 10")
        # check log
        log = utility.collect_log()
        assert utility.not_signed(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.error_response(message)

    ## 60 second spacing signed
    #
    def test_beacon_sp_60_signed(self):

        interval = 60
        utility.issue(utility.generate_signed(f"BeaconSp {interval}"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")
        # verify beacon interval
        log = utility.collect_two_beacons(interval)
        assert utility.beacon_interval(interval, log)
        # verify beacon messages
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)

    ## 120 second spacing signed
    #
    def test_beacon_sp_120_signed(self):

        interval = 120
        utility.issue(utility.generate_signed(f"BeaconSp {interval}"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")
        # verify beacon interval
        log = utility.collect_two_beacons(interval)
        assert utility.beacon_interval(interval, log)
        # verify beacon messages
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)

    ## 90 second spacing signed
    #
    def test_beacon_sp_90_signed(self):

        interval = 90
        utility.issue(utility.generate_signed(f"BeaconSp {interval}"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")
        # verify beacon interval
        log = utility.collect_two_beacons(interval)
        assert utility.beacon_interval(interval, log)
        # verify beacon messages
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)
        message = utility.collect_message()
        utility.local_beacon_message_sent(message)

    ## no beacon signed
    #
    def test_beacon_sp_0_signed(self):

        interval = 0
        utility.issue(utility.generate_signed(f"BeaconSp {interval}"))
        # check log
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert utility.no_logged_errors(log)
        assert utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.response_sent(message, "SBI")
        # verify no beacons sent
        assert utility.collect_timeout()

    ## error: no parameter signed
    #
    def test_beacon_sp_no_param_signed(self):

        utility.issue(utility.generate_signed("BeaconSp"))
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

    ## error: two parameters signed
    #
    def test_beacon_sp_two_param_signed(self):

        utility.issue(utility.generate_signed("BeaconSp 100 200"))
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

    ## error: invalid parameter signed
    #
    def test_beacon_sp_param_invalid_signed(self):

        utility.issue(utility.generate_signed("BeaconSp test"))
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.negative_acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.negative_acknowledged_message(message)

    ## error: parameter outside range signed
    #
    def test_beacon_sp_param_range_signed(self):

        utility.issue(utility.generate_signed("BeaconSp 10"))
        log = utility.collect_log()
        assert utility.signed(log)
        assert utility.signature_valid(log)
        assert utility.acknowledged_log(log)
        assert not utility.no_logged_errors(log)
        assert not utility.executed(log)
        # check messages
        message = utility.collect_message()
        assert utility.acknowledged_message(message)
        message = utility.collect_message()
        assert utility.error_response(message)
