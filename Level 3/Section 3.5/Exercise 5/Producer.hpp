/*
    File: Producer.hpp
    Description: Implement the producer class
*/

#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <thread>

#include "SyncPriorityQueue.hpp"
#include "Command.hpp"

// Class that produces objects and puts them in a queue
template <typename T, class M, typename F>
class Producer
{
private:
    int m_id; // The id of the producer
    SynchronisedQueue<T, M, F>* m_queue; // The queue pointer to use
public:
    // Constructor with id and the queue to use
    Producer(int id, SynchronisedQueue<T, M, F>* queue)
    {
        m_id = id; m_queue = queue;
    }
    // The thread function fills the queue with data
    void operator () (Command command)
    {
        while (true)
        {
            m_queue->Enqueue(command);

            // If this is a special command Object, stop producing
            if (command.isSpecial()) {
                break;
            }
            // Sleep one second
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};