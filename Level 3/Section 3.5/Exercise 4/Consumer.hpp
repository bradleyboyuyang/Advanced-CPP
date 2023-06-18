/*
    File: Consumer.hpp
    Description: Implement the consumer class
*/

#pragma once
#include <iostream>
#include <string>
#include <thread>
#include "SyncPriorityQueue.hpp"

// Class that consumes objects from a queue
template <class M, typename F>
class Consumer
{
private:
    int m_id; // The id of the consumer
    SynchronisedQueue<std::string, M, F>* m_queue; // The queue to use
public:
    // Constructor with id and the queue to use
    Consumer(int id, SynchronisedQueue<std::string, M, F>* queue)
    {
        m_id = id; m_queue = queue;
    }
    // The thread function reads data from the queue
    void operator () ()
    {
        while (true)
        {
            // Get the data from the queue and print it
            std::cout << "Dequeue: Consumer " << std::to_string(m_id).c_str() << " consumed (" << m_queue->Dequeue().c_str() << ")" << std::endl;
        }
    }
};