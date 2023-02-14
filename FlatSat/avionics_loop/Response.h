/**
 * @file Response.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat response messages
 * @version 1.0.0
 * @date 2023-02-03
 *
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
     *
     */

    Response(
        String content)
    {
        m_command = response;
        m_content = RES + content;
    }
};