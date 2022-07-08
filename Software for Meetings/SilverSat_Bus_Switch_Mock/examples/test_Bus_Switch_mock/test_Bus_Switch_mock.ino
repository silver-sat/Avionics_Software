//
// Mock Bus Switch test
// Lee A. Congdon
// 20 June 2022
//

#include <SilverSat_Bus_Switch_mock.h>

BusSwitch bus_switch;

void setup(void) {

    Serial.begin(115200);
    while (!Serial);
    auto start_time = millis();
    Serial.println();
    Serial.println("Starting Bus Switch Test");

    for (auto index = 1; index < 21; index++) {
        bus_switch.enableBus();
        bus_switch.disableBus();
        bus_switch.enableBus();
    }

    // Dump debug log

    auto count = bus_switch.getLogSize();
    Serial.print("There are "); Serial.print(count); Serial.println(" entries in the log");
    for (auto index = count; index > 0; index--) {
        auto log_entry = bus_switch.getLogEntry();
        Serial.print("Entry: "); 
        switch (log_entry.action)
        {
            case BusSwitch::Action::create:
                Serial.print("Created switch at ");
                break;
            case BusSwitch::Action::enable:
                Serial.print("Enabled switch at ");
                break;
            case BusSwitch::Action::disable:
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

