/**
 * @file payload_simulator_tester.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Avionics Board code to test the Payload Board simulator
 * @version 1.1.0
 * @date 2023-02-26
 *
 *
 */

constexpr unsigned PLD_ON_A_INT{17u}; /**< payload on A @hideinitializer */
constexpr unsigned PLD_ON_B_INT{18u}; /**< payload on B @hideinitializer */
constexpr unsigned PLD_ON_C_INT{8u};  /**< payload on C @hideinitializer */
constexpr unsigned STATES_A_INT{9u};  /**< payload state A @hideinitializer */
constexpr unsigned STATES_B_INT{2u};  /**< payload state B @hideinitializer */
constexpr unsigned STATES_C_INT{5u};  /**< payload state C @hideinitializer */
constexpr unsigned SHUTDOWN_A{19u};   /**< payload shutdown A @hideinitializer */
constexpr unsigned SHUTDOWN_B{36u};   /**< payload shutdown B @hideinitializer */
constexpr unsigned SHUTDOWN_C{37u};   /**< payload shutdown C @hideinitializer */
constexpr unsigned PAYLOAD_OC{16u};   /**< payload over current @hideinitializer */

void setup()
{

    Serial.begin(115200);
    while (!Serial)
        ;

    Serial.println("Simulator test initializing");
    pinMode(PLD_ON_A_INT, OUTPUT);
    pinMode(PLD_ON_B_INT, OUTPUT);
    pinMode(PLD_ON_C_INT, OUTPUT);
    pinMode(STATES_A_INT, OUTPUT);
    pinMode(STATES_B_INT, OUTPUT);
    pinMode(STATES_C_INT, OUTPUT);
    pinMode(SHUTDOWN_A, INPUT);
    pinMode(SHUTDOWN_B, INPUT);
    pinMode(SHUTDOWN_C, INPUT);

    Serial.println("Simulator test initialization complete");

    Serial.println("Powering down payload simulator");

    digitalWrite(PLD_ON_A_INT, HIGH);
    digitalWrite(PLD_ON_B_INT, HIGH);
    digitalWrite(PLD_ON_C_INT, HIGH);

    Serial.println("Delaying 10 seconds");

    delay(10 * 1000);

    Serial.println("Setting photo mode");

    digitalWrite(STATES_A_INT, LOW);
    digitalWrite(STATES_B_INT, LOW);
    digitalWrite(STATES_C_INT, LOW);

    Serial.println("Powering up payload simulator");

    digitalWrite(PLD_ON_A_INT, LOW);
    digitalWrite(PLD_ON_B_INT, LOW);
    digitalWrite(PLD_ON_C_INT, LOW);

    Serial.println("Waiting for simulator to initialize");
    delay(30 * 1000);

    Serial.println("Waiting for shutdown signal");

    {
        auto shutdown_a{digitalRead(SHUTDOWN_A)};
        auto shutdown_b{digitalRead(SHUTDOWN_B)};
        auto shutdown_c{digitalRead(SHUTDOWN_C)};
        do
        {
            shutdown_a = digitalRead(SHUTDOWN_A);
            shutdown_b = digitalRead(SHUTDOWN_B);
            shutdown_c = digitalRead(SHUTDOWN_C);
        } while ((shutdown_a + shutdown_b + shutdown_c) < 2);
    }

    Serial.println("Shutdown signal received");

    Serial.println("Waiting for shutdown completion");
    delay(30 * 1000);

    Serial.println("Powering down payload simulator");

    digitalWrite(PLD_ON_A_INT, HIGH);
    digitalWrite(PLD_ON_B_INT, HIGH);
    digitalWrite(PLD_ON_C_INT, HIGH);

    Serial.println("Delaying 10 seconds");

    delay(10 * 1000);

    Serial.println("Setting communications mode");

    digitalWrite(STATES_A_INT, HIGH);
    digitalWrite(STATES_B_INT, HIGH);
    digitalWrite(STATES_C_INT, HIGH);

    Serial.println("Powering up payload simulator");

    digitalWrite(PLD_ON_A_INT, LOW);
    digitalWrite(PLD_ON_B_INT, LOW);
    digitalWrite(PLD_ON_C_INT, LOW);

    Serial.println("Waiting for simulator to initialize");
    delay(30 * 1000);

    Serial.println("Waiting for shutdown signal");

    {
        auto shutdown_a = digitalRead(SHUTDOWN_A);
        auto shutdown_b = digitalRead(SHUTDOWN_B);
        auto shutdown_c = digitalRead(SHUTDOWN_C);
        do
        {
            shutdown_a = digitalRead(SHUTDOWN_A);
            shutdown_b = digitalRead(SHUTDOWN_B);
            shutdown_c = digitalRead(SHUTDOWN_C);
        } while ((shutdown_a + shutdown_b + shutdown_c) < 2);
    }

    Serial.println("Shutdown signal received");

    Serial.println("Waiting for shutdown completion");
    delay(30 * 1000);

    Serial.println("Powering down payload simulator");

    digitalWrite(PLD_ON_A_INT, HIGH);
    digitalWrite(PLD_ON_B_INT, HIGH);
    digitalWrite(PLD_ON_C_INT, HIGH);
}

void loop()
{
}