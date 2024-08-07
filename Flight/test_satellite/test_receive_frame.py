##
# @file test_receive_frame.py
# @brief FlatSat test Avionics Board receive frame processing
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 7 August 2024

"""Test Avionics Board receive frame processing"""

import common


## Test receive frame processing
#
class TestReceiveFrame:
    """Test receive frame processing"""

## Disable the beacon to avoid interference with the tests
    def test_disable_beacon(self):
        common.issue("BeaconSp 0")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_sp_pattern)

    def test_two_fends(self):
        common.command_port.write(common.FEND)
        common.issue("GetTelemetry")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.telemetry_pattern)

    def test_early_fend(self):
        common.command_port.write(common.FEND + common.REMOTE_FRAME + b"NoOp" + common.FEND + common.FEND)
        message = common.collect_message()
        assert common.verify_message(message, common.negative_acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.no_response_pattern)
    
    def test_fesc_tfend(self):
        common.command_port.write(common.FEND + common.REMOTE_FRAME + common.FESC + common.TFEND + common.FEND)
        message = common.collect_message()
        assert common.verify_message(message, common.negative_acknowledgment_pattern)
    
    def test_fesc_tfesc(self):
        common.command_port.write(common.FEND + common.REMOTE_FRAME + common.FESC + common.TFESC + common.FEND)
        message = common.collect_message()
        assert common.verify_message(message, common.negative_acknowledgment_pattern)
    
    def test_fesc_tfend_twice(self):
        common.command_port.write(common.FEND + common.REMOTE_FRAME + common.FESC + common.TFEND + common.FESC + common.TFEND + common.FEND)
        message = common.collect_message()
        assert common.verify_message(message, common.negative_acknowledgment_pattern)
    
    def test_fesc_outside_frame(self):
        common.command_port.write(common.FESC)
        message = common.collect_message()
        assert common.verify_message(message, common.no_response_pattern)

    def test_tfesc(self):
        common.command_port.write(common.FEND + common.REMOTE_FRAME + common.TFESC + common.FEND)
        message = common.collect_message()
        assert common.verify_message(message, common.no_response_pattern)
    
    def test_tfend(self):
        common.command_port.write(common.FEND + common.REMOTE_FRAME + common.TFEND + common.FEND)
        message = common.collect_message()
        assert common.verify_message(message, common.no_response_pattern)

    def test_data_outside_frame(self):
        common.command_port.write(common.REMOTE_FRAME)
        message = common.collect_message()
        assert common.verify_message(message, common.no_response_pattern)
    
    def test_fesc_other(self):
        common.command_port.write(common.FEND + common.REMOTE_FRAME + common.FESC + common.REMOTE_FRAME + common.FEND)
        message = common.collect_message()
        assert common.verify_message(message, common.no_response_pattern)
    

