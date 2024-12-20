##
# @brief FlatSat test Avionics Board day in the life scenario in one test
# @author Lee A. Congdon (lee@silversat.org)

"""FlatSat test Avionics Board day in the life scenario"""

import common
import test_day_in_the_life
from time import sleep

## Test day in the life
#
def test_package():

    """Test day in the life scenario"""

    test_class = test_day_in_the_life.TestDayInTheLife()

    sleep(45 * 60) # 45 minutes

    test_class.test_reset()
    
    test_class.test_no_operate()

    test_class.test_set_beacon_interval_1()

    test_class.test_get_beacon_interval()

    test_class.test_set_beacon_interval_2()

    test_class.test_set_realtime_clock()

    test_class.test_get_realtime_clock()

    test_class.test_paycomms_1()

    test_class.test_pictimes()

    test_class.test_paycomms_2()

    test_class.test_SSDVtimes()

    test_class.test_set_beacon_interval_3()
