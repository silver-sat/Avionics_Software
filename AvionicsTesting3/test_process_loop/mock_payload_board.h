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
     * @return true successful
     * @return false error
     */

    bool begin();

    /**
     * @brief Power up Payload Board and take photo
     *
     * @return true successful
     * @return false error
     */
    bool photo();

    /**
     * @brief Power up Payload Board and tweet
     *
     * @return true successful
     * @return false error
     */
    bool tweet();

    /**
     * @brief Shut off Payload Board if ready to sleep
     *
     * @return true successful
     * @return false error
     */
    bool check_shutdown();

    /**
     * @brief End payload session
     *
     * @return true successful
     * @return false error
     */

    bool end_activity();

    /**
     * @brief Get the photo count
     * 
     */

    int get_photo_count();

private:
    /**
     * @brief Power down Payload board
     *
     * @return true successful
     * @return false error
     */
    bool power_down();

    /**
     * @brief Power up Payload Board
     *
     * @return true successful
     * @return false error
     */
    bool power_up();

    /**
     * @brief Set the mode to communications
     *
     * @return true successful
     * @return false error
     */
    bool set_mode_comms();

    /**
     * @brief Set the mode to photograph
     *
     * @return true successful
     * @return false error
     */
    bool set_mode_photo();

    /**
     * @brief Check Payload Board shutdown signal
     *
     * @return true successful
     * @return false error
     */
    bool power_down_signal_is_set();

private:
    const unsigned long _tweet_duration{30 * SECONDS_TO_MILLISECONDS};
    const unsigned long _photo_duration{15 * SECONDS_TO_MILLISECONDS};
    unsigned long _last_activity_time{0};
    unsigned long _action_duration{};
    bool _payload_active{false};
    bool _power_down_signal{true};
    int _photo_count{0};
};

#endif // MOCK_PAYLOAD_BOARD_H