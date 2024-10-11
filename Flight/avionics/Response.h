/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat response messages
 *
 * This file implements the Response class
 *
 */

#pragma once

#include "Message.h"
#include "avionics_constants.h"
#include <Arduino.h>

/**
 * @brief Response message
 *
 */
class Response final : public Message
{
public:
    /**
     * @brief Construct a new Response::Response object
     *
     * @param content contents of the response
     *
     */

    explicit Response(const String content)
    {
        m_command = response;
        m_content = RES + " " + content;
    }
};