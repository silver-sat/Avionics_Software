##
# @brief Test Avionics Board commands
# @author Lee A. Congdon (lee@silversat.org)

"""Test Avionics Board commands"""

import common


## Test commands
#
class TestCommands:
    """Test commands"""

    def test_set_realtime_clock(self):
        common.issue(f"SetClock {common.now()}")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.set_clock_pattern)

    def test_set_beacon_interval(self):
        common.issue("BeaconSp 60")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_sp_pattern)

    def test_pictimes(self):
        common.issue(f"PicTimes {common.now1m()}")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.pic_times_pattern)

    def test_SSDVtimes(self):
        common.issue(f"SSDVTimes {common.now1m()}")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.SSDV_times_pattern)

    def test_clear_payload_queue(self):
        common.issue(f"ClearPayloadQueue")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.clear_payload_queue_pattern)

    def test_get_realtime_clock(self):
        common.issue("ReportT")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.reportt_pattern)

    def test_unset_clock(self):
        common.issue(f"UnsetClock")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.unset_clock_pattern)

    def test_get_payload_queue(self):
        common.issue("GetPayloadQueue")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.get_payload_queue_pattern)

    def test_get_telemetry(self):
        common.issue("GetTelemetry")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.telemetry_pattern)

    def test_get_power(self):
        common.issue("GetPower")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.power_pattern)

    def test_get_comms(self):
        common.issue("GetComms")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.comms_pattern)

    def test_get_beacon_interval(self):
        common.issue("GetBeaconInterval")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_interval_pattern)

    def test_no_operate(self):
        common.issue("NoOperate")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.no_operation_pattern)

    def test_send_packet(self):
        common.issue("SendTestPacket")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.test_packet_pattern)

    def test_paycomms(self):
        common.issue("PayComms")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.pay_comms_pattern)

    def test_twee_slee(self):
        common.issue("TweeSlee")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.twee_slee_pattern)

    def test_watchdog(self):
        common.issue("Watchdog")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.watchdog_pattern)

    def test_modify_mode(self):
        common.issue("ModifyMode 1")
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.modify_mode_pattern)
