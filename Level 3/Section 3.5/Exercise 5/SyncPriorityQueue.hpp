/*
    File: SyncPriorityQueue.hpp
    Description: Implement a generic synchronising priority queue having an embedded STL priority queue,
    both the latter's container type and comparator are generic
*/

#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <queue>
#include <mutex>
#include <thread>

#include "Command.hpp"

// Queue class that has thread synchronisation
// As required, the data type, container type and comparator are generic
template <typename T, class M, typename F>
class SynchronisedQueue {
private:
    std::priority_queue<T, M, F> m_queue; // Use stl queue to store data
    std::mutex m_mutex; // The mutex to synchronise on
    std::condition_variable m_cond; // The condition to wait for
public:
    // Add data to the queue and notify others
    void Enqueue(const T& data)
    {
        // Acquire lock on the queue
        std::unique_lock<std::mutex> lock(m_mutex);
        // Add the data to the queue
        m_queue.push(data);

        std::cout << "Enqueue: Command ID " << data.priority() << std::endl;
        // Notify others that data is ready
        m_cond.notify_one();
    } // Lock is released here

    // Get data from the queue. Wait for data if not available
    T Dequeue()
    {
        // Acquire lock on the queue
        std::unique_lock<std::mutex> lock(m_mutex);
        // When there is no data, wait till someone fills it
        // Lock is automatically released in the wait and active again after the wait
        while (m_queue.size() == 0) m_cond.wait(lock);
        // Retrieve the data from the queue
        T result = m_queue.top(); m_queue.pop();
        std::cout << "Dequeue: Command ID " << result.priority() << std::endl;
        return result;
    } // Lock is released here

    // return the size of the queue
    std::size_t Size() {
        return m_queue.size();
    }
};