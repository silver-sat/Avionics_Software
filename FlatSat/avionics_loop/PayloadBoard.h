/**
 * @file PayloadBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Payload Board
 * @version 1.1.0
 * @date 2022-07-24
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
    bool check_shutdown();

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

    Beacon::PayloadStatus get_status();

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
     * @brief Evaluate power down signal
     *
     */
    bool shutdown_signal_is_set() const;

private:
    bool m_payload_active{false};              /**< payload in photo or communications mode */
    long unsigned int m_start_time{};          /**< delay for payload to pull shutdown lines low */
    bool m_in_shutdown_delay{false};           /**< payload in shutdown delay state after setting shutdown lines */
    long unsigned int m_shutdown_start_time{}; /**< delay for payload to complete shutdown */
    // beacon data
    bool m_last_session_normal{false};                                      /**< last session completed normally */
    bool m_timeout_occurred{false};                                         /**< set true if Payload Board times out */
};