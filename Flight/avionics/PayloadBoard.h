/**
 * @file PayloadBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Payload Board
 * @version 1.1.1
 * @date 2022-07-24
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
};

/**
 * @brief SilverSat Payload Board
 *
 */

class PayloadBoard final
{
public:
    /**
     * @brief Initialize Payload Board
     *
     *
     */

    bool begin();

    /**
     * @brief Power up Payload Board and take photo
     *
     */
    bool photo();

    /**
     * @brief Power up Payload Board and communicate
     *
     */
    bool communicate();

    /**
     * @brief Shut off Payload Board if ready to sleep
     *
     */
    void check_shutdown();

    /**
     * @brief Get the payload activity status
     *
     */

    bool get_payload_active() const;

    /**
     * @brief Power down Payload Board
     *
     */
    bool power_down();

    /**
     * @brief Get status for beacon
     *
     */

    PayloadBeacon get_status();

private:
    /**
     * @brief Power up Payload Board
     *
     */
    bool power_up();

    /**
     * @brief Set the mode to communications
     *
     */
    bool set_mode_comms();

    /**
     * @brief Set the mode to photograph
     *
     */
    bool set_mode_photo();

    /**
     * @brief Shutdown vote
     *
     */
    bool shutdown_vote();

    /**
     * @brief Check timeout
     *
     */
    void check_timeout();

    /**
     * @brief Check overcurrent
     *
     */
    void check_overcurrent();

    PayloadState m_state{PayloadState::off};                                /**< current state of payload board */
    PayloadActivity m_activity{PayloadActivity::none};                      /**< current activity of payload board */
    long unsigned int m_payload_start_time{};                               /**< beginning of last payload activity from millis() */
    long unsigned int m_shutdown_start_time{};                              /**< beginning of shutdown delay from millis() */
    long unsigned int m_last_payload_duration{};                            /**< duration of last payload activity */
    bool m_timeout_occurred{false};                                         /**< true if Payload Board timeout */
    bool m_overcurrent_occurred{false};                                     /**< true if Payload Board overcurrent */
};