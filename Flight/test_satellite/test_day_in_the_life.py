##
# @brief FlatSat test Avionics Board day in the life scenario
# @author Lee A. Congdon (lee@silversat.org)

"""FlatSat test Avionics Board day in the life scenario"""

import common
from time import sleep


## Test day in the life
#
class TestDayInTheLife:
    """Test day in the life scenario"""

    def test_reset(self):
        common.issue("BeaconSp 0")
        sleep(5)
        common.read() # clear buffer

    def test_no_operate(self):
        common.issue("NoOperate")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.no_operation_pattern)

    def test_set_beacon_interval_1(self):
        common.issue("BeaconSp 60")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_sp_pattern)

    def test_get_beacon_interval(self):
        common.issue("GetBeaconInterval")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_interval_pattern)

    def test_set_beacon_interval_2(self):
        common.issue("BeaconSp 0")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_sp_pattern)

    def test_set_realtime_clock(self):
        common.issue(f"SetClock {common.now()}")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.set_clock_pattern)

    def test_get_realtime_clock(self):
        common.issue("ReportT")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.reportt_pattern)

    def test_paycomms_1(self):
        common.issue("PayComms")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.pay_comms_pattern)
        sleep(205 + 30) # predicted time plus buffer

    def test_pictimes(self):
        common.issue(f"PicTimes {common.now1m()}")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.pic_times_pattern)
        sleep(162 + 60 + 30) # predicted time plus delay for picture time start plus buffer

    def test_paycomms_2(self):
        common.issue("PayComms")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.pay_comms_pattern)
        sleep(205 + 30) # predicted time plus buffer

    def test_SSDVtimes(self):
        common.issue(f"SSDVTimes {common.now1m()}")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.SSDV_times_pattern)
        sleep(162 + 60 + 30) # predicted time plus delay for SSDV time start plus buffer

    def test_set_beacon_interval_3(self):
        common.issue("BeaconSp 180")
        sleep(5)
        message = common.collect_message()
        assert common.verify_message(message, common.acknowledgment_pattern)
        message = common.collect_message()
        assert common.verify_message(message, common.beacon_sp_pattern)
