/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Payload Board
 *
 * This file declares the class which interfaces with the Payload Board
 *
 */

#pragma once

#include "avionics_constants.h"
#include "Beacon.h"

/**
 * @brief SilverSat Payload Board
 *
 */

class PayloadBoard final
{
public:
    bool begin();
    bool photo();
    bool SSDV();
    bool communicate();
    void check_shutdown();
    bool power_down();
    bool get_payload_active() const;
    PayloadBeacon get_status();

private:
    /**
     * @brief Payload states
     *
     * States correspond to status of payload board
     *
     */

    enum class PayloadState
    {
        off,
        user_state_wait,
        photo,
        communications,
        signal_SSDV,
        SSDV,
        shutdown,
        timeout,
        overcurrent,
    };

    /**
     * @brief PayloadActivity to be performed
     *
     */

    enum class PayloadActivity
    {
        none,
        photo,
        communications,
        SSDV,
    };

    /**
     * @brief Payload activity duration intervals
     *
     */

    enum class DurationInterval
    {
        less_than_1_minute,
        between_1_and_2_minutes,
        between_2_and_4_minutes,
        between_4_and_6_minutes,
        between_6_and_8_minutes,
        between_8_and_10_minutes,
        forced_shutdown,
        count
    };

    /**
     * @brief Payload Beacons
     *
     */

    /**
     * @brief Payload Beacons
     *
     */

    const PayloadBeacon overcurrent_beacons[static_cast<size_t>(DurationInterval::count)] = {
        PayloadBeacon::overcurrent_0_1,
        PayloadBeacon::overcurrent_1_2,
        PayloadBeacon::overcurrent_2_4,
        PayloadBeacon::overcurrent_4_6,
        PayloadBeacon::overcurrent_6_8,
        PayloadBeacon::overcurrent_8_10,
        PayloadBeacon::overcurrent_timeout,
    };

    const PayloadBeacon photo_beacons[static_cast<size_t>(DurationInterval::count)] = {
        PayloadBeacon::photo_0_1,
        PayloadBeacon::photo_1_2,
        PayloadBeacon::photo_2_4,
        PayloadBeacon::photo_4_6,
        PayloadBeacon::photo_6_8,
        PayloadBeacon::photo_8_10,
        PayloadBeacon::photo_timeout,
    };

    const PayloadBeacon communicate_beacons[static_cast<size_t>(DurationInterval::count)] = {
        PayloadBeacon::communicate_0_1,
        PayloadBeacon::communicate_1_2,
        PayloadBeacon::communicate_2_4,
        PayloadBeacon::communicate_4_6,
        PayloadBeacon::communicate_6_8,
        PayloadBeacon::communicate_8_10,
        PayloadBeacon::communicate_timeout,
    };

    const PayloadBeacon SSDV_beacons[static_cast<size_t>(DurationInterval::count)] = {
        PayloadBeacon::SSDV_0_1,
        PayloadBeacon::SSDV_1_2,
        PayloadBeacon::SSDV_2_4,
        PayloadBeacon::SSDV_4_6,
        PayloadBeacon::SSDV_6_8,
        PayloadBeacon::SSDV_8_10,
        PayloadBeacon::SSDV_timeout,
    };

    bool check_startup();

    bool power_up();
    bool set_mode_comms();
    bool set_mode_photo();
    bool set_mode_SSDV_start();
    bool set_mode_SSDV_transition();
    bool shutdown_vote();
    void check_timeout();
    void check_overcurrent();
    DurationInterval get_duration_interval(unsigned long duration_ms);

    PayloadState m_state{PayloadState::off};           /**< current state of payload board */
    PayloadActivity m_activity{PayloadActivity::none}; /**< current activity of payload board */
    long unsigned int m_payload_start_time{};          /**< beginning of last payload activity from millis() */
    long unsigned int m_shutdown_start_time{};         /**< beginning of shutdown delay from millis() */
    long unsigned int m_last_payload_duration{};       /**< duration of last payload activity */
    long unsigned int m_SSDV_signal_start_time{};      /**< beginning of signal delay for SSDV mode */
    bool m_timeout_occurred{false};                    /**< true if Payload Board timeout */
    bool m_overcurrent_occurred{false};                /**< true if Payload Board overcurrent */
};