/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Payload Queue
 *
 * This file declares the class which implements the PayloadQueue queue
 *
 */

#pragma once

#include "RTClib.h"

/**
 * @brief Define the maximum size of the queue
 *
 */

static constexpr size_t maximum_payload_queue_size{100};

/**
 * @brief Define the PayloadQueue class
 *
 */

class PayloadQueue
{

    /**
     * @brief Define the ActivityType enum class
     *
     */

    enum ActivityType
    {
        Photo,
        SSDV,
    };

    /**
     * @brief Define the PayloadQueue struct
     *
     */

    struct Element

    {
        DateTime time;
        ActivityType type;

        // Constructor for convenience
        Element(DateTime time, ActivityType type) : time(time), type(type) {}
    };

public:
    bool push(const Element &payload);
    Element pop();
    bool empty() const;
    size_t size() const;

private:
    PayloadQueue::Element m_payload_queue[maximum_payload_queue_size]; // Array to store the payloads
    size_t m_payload_queue_size = 0;                                   // Current number of elements in the queue
};