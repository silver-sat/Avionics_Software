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
    bool get_payload_active() const;
    bool power_down();
    PayloadBeacon get_status();
private:
    bool power_up();
    bool set_mode_comms();
    bool set_mode_photo();
    bool set_mode_SSDV_start();
    bool set_mode_SSDV_transition();
    bool shutdown_vote();
    void check_timeout();
    void check_overcurrent();

    PayloadState m_state{PayloadState::off};                                /**< current state of payload board */
    PayloadActivity m_activity{PayloadActivity::none};                      /**< current activity of payload board */
    long unsigned int m_payload_start_time{};                               /**< beginning of last payload activity from millis() */
    long unsigned int m_shutdown_start_time{};                              /**< beginning of shutdown delay from millis() */
    long unsigned int m_last_payload_duration{};                            /**< duration of last payload activity */
    long unsigned int m_SSDV_signal_start_time{};                                /**< beginning of signal delay for SSDV mode */
    bool m_timeout_occurred{false};                                         /**< true if Payload Board timeout */
    bool m_overcurrent_occurred{false};                                     /**< true if Payload Board overcurrent */
};