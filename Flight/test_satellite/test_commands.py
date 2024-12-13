##
# @brief Test Avionics Board commands
# @author Lee A. Congdon (lee@silversat.org)

"""Test Avionics Board commands"""

import common
import time

## Test commands
#
class TestCommands:
    """Test commands"""

    def test_reset(self):
        # time.sleep((30 + 45 + 15) * 60) # wait for the satellite to boot
        common.issue("BeaconSp 0")
        time.sleep(5)
        common.read() # clear buffer
    
    def test_set_realtime_clock(self):
        common.issue(f"SetClock {common.now()}")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.set_clock_pattern)

    def test_set_beacon_interval(self):
        common.issue("BeaconSp 60")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_sp_pattern)

    def test_pictimes(self):
        common.issue(f"PicTimes {common.now30s()}")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.pic_times_pattern)
        time.sleep(300) # wait for the satellite to take a picture

    def test_SSDVtimes(self):
        common.issue(f"SSDVTimes {common.now30s()}")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.SSDV_times_pattern)
        time.sleep(300) # wait for the satellite to complete the SSDV transmission

    def test_clear_payload_queue(self):
        common.issue(f"ClearPayloadQueue")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.clear_payload_queue_pattern)

    def test_get_realtime_clock(self):
        common.issue("ReportT")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.reportt_pattern)

    def test_get_payload_queue(self):
        common.issue("GetPayloadQueue")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.payload_queue_pattern)

    def test_get_telemetry(self):
        common.issue("GetTelemetry")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.telemetry_pattern)

    def test_get_power(self):
        common.issue("GetPower")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.power_pattern)

    def test_get_comms(self):
        common.issue("GetComms")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.comms_pattern)

    def test_get_beacon_interval(self):
        common.issue("GetBeaconInterval")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_interval_pattern)

    def test_paycomms(self):
        common.issue("PayComms")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.pay_comms_pattern)
        time.sleep(300) # wait for the satellite to complete the communications session

    def test_twee_slee(self):
        common.issue("TweeSlee")
        time.sleep(5)
        # does not return an acknowledgment due to radio shutdown
        # message = common.collect_message()
        # assert common.verify_message(message, common.acknowledgment_pattern)
        # message = common.collect_message()
        # assert common.verify_message(message, common.twee_slee_pattern)

    # def test_watchdog(self):
    # creates a hard loop if watchdog is not jumpered on the avionics board
    #     time.sleep(5)
    #     common.issue("Watchdog")
    #     message = common.collect_message()
    #     assert common.verify_message(message, common.acknowledgment_pattern)
    #     message = common.collect_message()
    #     assert common.verify_message(message, common.watchdog_pattern)

    def test_no_operate(self):
        common.issue("NoOperate")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.no_operation_pattern)

    def test_send_packet(self):
        common.issue("SendTestPacket")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.test_packet_pattern)

    def test_unset_clock(self):
        common.issue(f"UnsetClock")
        time.sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.unset_clock_pattern)

    def test_log_arguments(self):
        common.issue("LogArguments 1 2 3 4 5 6")
        time.sleep(5)

    def test_background_rssi(self):
        common.issue("BackgroundRSSI 10")
        time.sleep(35)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.background_rssi_pattern)

    def test_current_rssi(self):
        common.issue("CurrentRSSI")
        time.sleep(5)
        # current RSSI does not return data to the ground
        # message = common.collect_message()
        # assert common.verify_message(message, common.acknowledgment_pattern)
        # message = common.collect_message()
        # assert common.verify_message(message, common.current_rssi_pattern)