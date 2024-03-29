##
# @file test_commands.py
# @brief FlatSat test Avionics Board commands
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 9 October 2022

"""FlatSat test Avionics Board commands"""

import common


## Test commands
#
class TestCommands:
    """Test commands"""

    def test_set_realtime_clock(self):
        common.issue(f'SetClock {common.now()}')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.set_clock_pattern)

    def test_set_beacon_interval(self):
        common.issue('BeaconSp 60')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_sp_pattern)

    def test_pictimes(self):
        common.issue(f'PicTimes {common.now1m()}')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.pic_times_pattern)

    def test_clear_pictimes(self):
        common.issue(f'ClearPicTimes')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.clear_pic_times_pattern)

    def test_unset_clock(self):
        common.issue(f'UnsetClock {common.now1m()}')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.unset_clock_pattern)

    def test_get_realtime_clock(self):
        common.issue('ReportT')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.reportt_pattern)

    def test_get_pictimes(self):
        common.issue('GetPicTimes')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.get_pic_times_pattern)

    def test_get_telemetry(self):
        common.issue('GetTelemetry')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.telemetry_pattern)

    def test_get_power(self):
        common.issue('GetPower')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.power_pattern)

    def test_get_comms(self):
        common.issue('GetComms')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.comms_pattern)

    def test_get_beacon_interval(self):
        common.issue('GetBeaconInterval')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_interval_pattern)

    def test_no_operate(self):
        common.issue('NoOperate')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.no_operation_pattern)

    def test_send_packet(self):
        common.issue('SendTestPacket')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.test_packet_pattern)

    def test_paycomms(self):
        common.issue('PayComms')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.pay_comms_pattern)

    def test_twee_sell(self):
        common.issue('TweeSlee')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.twee_slee_pattern)

    def test_watchdog(self):
        common.issue('ExternalWatchdog')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.watchdog_pattern)

    def test_modify_frequency(self):
        common.issue('ModifyFrequency 123456789')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.modify_frequency_pattern)

    def test_modify_mode(self):
        common.issue('ModifyMode 1')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.modify_mode_pattern)

    def test_adjust_frequency(self):
        common.issue('AdjustFrequency 123456789')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.adjust_frequency_pattern)

    def test_transmit_cw(self):
        common.issue('TransmitCW 12')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.transmit_CW_pattern)

    def test_background_rssi(self):
        common.issue('BackgroundRSSI 12')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.background_RSSI_pattern)

    def test_current_rssi(self):
        common.issue('CurrentRSSI')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.current_RSSI_pattern)

    def test_sweep_transmitter(self):
        common.issue('SweepTransmitter 123456789 123456789 123 123')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.sweep_transmitter_pattern)

    def test_sweep_receiver(self):
        common.issue('SweepReceiver 123456789 123456789 123 123')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.sweep_receiver_pattern)

    def test_query_register(self):
        common.issue('QueryRegister 12345')
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.query_register_pattern)
