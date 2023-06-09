/**
 * @file enum.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstration of scoped enum
 * @version 1.0.0
 * @date 2023-06-09
 *
 *
 */

enum class LastSessionType {
  none,
  comms,
  photo,
  overcurrent,
  unknown,
};

const String get_last_session_type(LastSessionType last_session_type) {
  switch (last_session_type) {
    case LastSessionType::none: return ("None");
    case LastSessionType::comms: return ("Comms");
    case LastSessionType::photo: return ("Photo");
    case LastSessionType::overcurrent: return ("Overcurrent");
    default: return ("Unknown");
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }

  LastSessionType payload_session{LastSessionType::comms};
  Serial.println("The last session type was " + get_last_session_type(payload_session));
}

void loop() {
}