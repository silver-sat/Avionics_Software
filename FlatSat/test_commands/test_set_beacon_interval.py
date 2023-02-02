##
# @file test_set_beacon_interval.py
# @brief FlatSat test Avionics Board BeaconSp command
# @author Lee A. Congdon (lee@silversat.org)
# @version 2.0.0
# @date 21 August 2022

"""FlatSat test Avionics Board BeaconSp command"""

import helper

## Test BeaconSp command
#


class TestBeaconSp:
    """Test BeaconSp command"""



    ## no beacon
    #
    def test_beacon_sp_0(self):

        interval = 0
        # todo: fix single and double 0 error
        helper.issue(f"BeaconSp 000")
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message)
    
    ## no beacon signed
    #
    def test_beacon_sp_0(self):

        interval = 0
        # todo: fix single and double 0 error
        helper.issue(helper.generate_signed(f"BeaconSp 000"))
        message = helper.collect()
        assert helper.acknowledged(message)
        message = helper.collect()
        assert helper.response_sent(message)
