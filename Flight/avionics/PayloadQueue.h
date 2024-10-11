/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Payload Queue
 *
 * This file declares the class which implements the PayloadQueue queue
 *
 */

#pragma once

#include <RTClib.h>

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
public:
    PayloadQueue() : m_size(0) {}

    /**
     * @brief Define the ActivityType enum class
     *
     */

    enum ActivityType
    {
        Unknown,
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

        Element() : time(DateTime(0, 0, 0, 0, 0, 0)), type(ActivityType::Photo) {}
        Element(DateTime time, ActivityType type) : time(time), type(type) {}
    };

    bool push(const Element &payload);
    Element pop();
    Element peek() const;
    bool empty() const;
    size_t size() const;
    void clear();
    PayloadQueue::Element& operator[](size_t index);
    const String activity_name(PayloadQueue::ActivityType type) const;


private:
    Element m_array[maximum_payload_queue_size]; // Array to store the payloads
    size_t m_size = 0;                                   // Current number of elements in the queue
};