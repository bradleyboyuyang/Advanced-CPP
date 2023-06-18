/*
    File: Producer.hpp
    Description: Implement the producer class
*/

#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <thread>

#include "SyncQueue.hpp"

// Class that produces objects and puts them in a queue
class Producer
{
private:
    int m_id; // The id of the producer
    SynchronisedQueue<std::string>* m_queue; // The queue pointer to use
public:
    // Constructor with id and the queue to use
    Producer(int id, SynchronisedQueue<std::string>* queue)
    {
        m_id = id; m_queue = queue;
    }
    // The thread function fills the queue with data
    void operator () ()
    {
        int data = 0;
        while (true)
        {
            // Produce a string and store in the queue
            std::string str = "Producer: " + std::to_string(m_id) + " data: " + std::to_string(data++);
            m_queue->Enqueue(str);
            std::cout << "Enqueue: " << str << std::endl;
            // Sleep one second
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};