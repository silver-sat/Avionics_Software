/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Payload queue
 *
 * This file implements the class which manaages the with PayloadQueue queue
 *
 */

#include "PayloadQueue.h"
#include "log_utility.h"

/**
 * @brief Template for swap function
 *
 */

template <typename T>
void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

/**
 * @brief Add an element to the queue
 *
 * @param payload a PayloadQueue element
 *
 * @return bool true if successful
 * @return bool false if error
 *
 */

bool PayloadQueue::push(const PayloadQueue::Element &payload)
{
    // todo: consider heap or linked list if insertion time is excessive
    if (m_payload_queue_size >= maximum_payload_queue_size)
    {
        Log.errorln("Payload queue is full");
        return false;
    }
    // If the queue is empty or the new payload has lower priority (later time)
    if (empty() || payload.time >= m_payload_queue[m_payload_queue_size - 1].time)
    {
        m_payload_queue[m_payload_queue_size++] = payload; // Add the new payload at the end
        // Sort the queue to maintain priority order
        for (size_t i = m_payload_queue_size - 1; i > 0 && m_payload_queue[i].time < m_payload_queue[i - 1].time; --i)
        {
            swap(m_payload_queue[i], m_payload_queue[i - 1]);
        }
    }
    else
    {
        // Find the correct position to insert the payload while maintaining order
        size_t i = m_payload_queue_size;
        m_payload_queue[m_payload_queue_size++] = payload;
        while (i > 0 && m_payload_queue[i].time < m_payload_queue[i - 1].time)
        {
            swap(m_payload_queue[i], m_payload_queue[i - 1]);
            --i;
        }
    }
    return true;
}

/**
 * @brief Remove the highest priority payload from the queue
 *
 * @return
 */

PayloadQueue::Element PayloadQueue::pop()
{
    if (empty())
    {
        return PayloadQueue::Element(DateTime(0, 0, 0, 0, 0, 0), PayloadQueue::Photo);
    }
    PayloadQueue::Element head = m_payload_queue[0];
    // Shift all elements one position to the left to remove the head
    for (size_t i = 0; i < m_payload_queue_size - 1; ++i)
    {
        m_payload_queue[i] = m_payload_queue[i + 1];
    }
    --m_payload_queue_size;
    return head;
}

// Check if the queue is empty
bool PayloadQueue::empty() const
{
    return m_payload_queue_size == 0;
}

// Get the number of elements in the queue
size_t PayloadQueue::size() const
{
    return m_payload_queue_size;
}