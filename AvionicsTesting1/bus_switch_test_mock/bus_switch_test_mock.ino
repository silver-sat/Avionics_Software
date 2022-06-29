//
// Mock Bus Switch test
// Lee A. Congdon
// 20 June 2022
//

#include "bus_switch_mock.h"

BusSwitch bus_switch;

void setup(void) {

    Serial.begin(115200);
    while (!Serial);
    auto start_time = millis();
    Serial.println();
    Serial.println("Starting Bus Switch Test");

    for (auto index = 1; index < 21; index++) {
        bus_switch.enable();
        bus_switch.disable();
        bus_switch.enable();
    }

    // Dump debug log

    auto count = bus_switch._debug_log.size();
    Serial.print("There are "); Serial.print(count); Serial.println(" entries in the log");
    for (auto index = count; index > 0; index--) {
        auto log_entry = bus_switch._debug_log.shift();
        Serial.print("Entry: "); 
        switch (log_entry.action)
        {
            case CREATE:
                Serial.print("Created switch at ");
                break;
            case ENABLE:
                Serial.print("Enabled switch at ");
                break;
            case DISABLE:
                Serial.print("Disabled switch at ");
                break;
        }
        Serial.println(log_entry.time_stamp);
    }
  Serial.print("Completed Bus Switch Test in "); Serial.print( (millis() - start_time) / 1000.0, 3 ); Serial.println(" seconds");

}

void loop(void) {
    while(true);
}

