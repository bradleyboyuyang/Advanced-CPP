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
template <typename T, class M, typename F>
class Consumer
{
private:
    int m_id; // The id of the consumer
    SynchronisedQueue<T, M, F>* m_queue; // The queue to use
public:
    // Constructor with id and the queue to use
    Consumer(int id, SynchronisedQueue<T, M, F>* queue)
    {
        m_id = id; m_queue = queue;
    }
    // The thread function reads data from the queue
    void operator () ()
    {
        while (true)
        {
            Command command = m_queue->Dequeue();
            // As required, consumers need to recognize a special command object to know that there is no more input
            // If this is a special command object, stop dequeueing
            if (command.isSpecial()) {
                break;
            }

        }
    }
};