/*
    Level 3.1: Threads
    Problem 4: Synchronising Queue

    Name: Boyu Yang

    File: Exercise 4.cpp
    Description: Main file for execution
    
    Problem objective:
    We implement a synchronising (thread-safe) FIFO queue in C++11. In this exercise we create our own
    generic synchronising queue having an embedded STL queue.
    a) Implement this template class, in particular its template parameters and functions for queueing and dequeing.
    b) Add locking mechanisms to functions for synchronisation effects.
    c) Add notification mechanisms to allow thread notification (use condition variables for notification).
    d) Test the queue by creating producer and consumer threads.

*/

#include <boost/thread.hpp>

#include "Consumer.hpp"
#include "Producer.hpp"


int main() {
    /// d) Test the queue by creating producer and consumer threads.
        // The number of producers/consumers
    int nrProducers = 3, nrConsumers = 3;
    // The shared queue
    SynchronisedQueue<std::string> queue;
    // Create producers
    boost::thread_group producers;
    for (int i = 0; i < nrProducers; i++)
    {
        Producer p(i, &queue);
        producers.create_thread(p);
    }
    // Create consumers
    boost::thread_group consumers;
    for (int i = 0; i < nrConsumers; i++)
    {
        Consumer c(i, &queue);
        consumers.create_thread(c);
    }
    // Wait for enter
    getchar();
    // Interrupt the threads and stop them
    producers.interrupt_all(); producers.join_all();
    consumers.interrupt_all(); consumers.join_all();
}