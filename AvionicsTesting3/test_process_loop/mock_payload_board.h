/**
 * @file mock_payload_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Payload Board
 * @version 1.0.0
 * @date 2022-07-24
 *
 *
 */

#ifndef MOCK_PAYLOAD_BOARD_H
#define MOCK_PAYLOAD_BOARD_H

#include "board_configuration.h"

/**
 * @brief Mock Payload Board constants
 *
 */

constexpr unsigned long tweet_duration{30 * seconds_to_milliseconds}; /**< test tweet duration */
constexpr unsigned long photo_duration{15 * seconds_to_milliseconds}; /**< test photo duration */

/**
 * @brief Mock Payload Board for testing the Avionics Board
 *
 */

class MockPayloadBoard
{
public:
    /**
     * @brief Construct a new Mock Payload Board object
     *
     */

    MockPayloadBoard();

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
     * @brief Power up Payload Board and tweet
     *
     */
    bool tweet();

    /**
     * @brief Shut off Payload Board if ready to sleep
     *
     */
    bool check_shutdown();

    /**
     * @brief End payload session
     *
     */

    bool end_activity();

    /**
     * @brief Get the photo count
     *
     */

    int get_photo_count();

    /**
     * @brief Get the payload activity status
     *
     */

    bool get_payload_active();

    /**
     * @brief Power down Payload board
     *
     */
    bool power_down();

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
     * @brief Check Payload Board shutdown signal
     *
     */
    bool power_down_signal_is_set();

private:
    unsigned long m_last_activity_time{0};
    unsigned long m_action_duration{};
    bool m_payload_active{false};
    bool m_power_down_signal{true};
    int m_photo_count{0};
};

#endif // MOCK_PAYLOAD_BOARD_H