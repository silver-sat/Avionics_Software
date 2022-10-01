/**
 * @file blink_without_delay.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Blink LED with no delay statement
 * @version 1.0.0
 * @date 2022-09-01
 */

constexpr unsigned long cycle_length{1000};
unsigned long cycle_start{0};
bool LED_on{false};

void setup() {
  // put your setup code here, to run once:
  pinMode (LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long interval = millis() - cycle_start;
  if (interval > cycle_length) {
    if (LED_on) {
      LED_on = false;
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      LED_on = true;
      digitalWrite(LED_BUILTIN, HIGH);
    }
    cycle_start = millis();
  }
  
}
