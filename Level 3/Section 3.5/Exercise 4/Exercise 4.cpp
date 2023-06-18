/*
    Level 3.5: Complexity and STL Containers
    Problem 4: Synchronising Queue

    Name: Boyu Yang

    Problem objective:
    We have already discussed synchronising (thread-safe) FIFO queues. In this exercise we create our own
    generic synchronising queue having an embedded STL priority queue (both the latter’s container type and
    comparator are generic).
    Answer the following questions:
    a) Implement this template class, in particular its template parameters and functions for queueing and dequeuing.
    b) Add locking mechanisms to functions for synchronisation effects.
    c) Add notification mechanisms to allow thread notification.
    d) Test the new class.

*/

#include <thread>
#include "Consumer.hpp"
#include "Producer.hpp"

// simple function to check whether a thread has completed and join it if yes
void join(std::thread& t) {
    if (t.joinable()) {
        t.join();
    }
    else {
        try {
            t.join();
        }
        catch (std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
    }
}

int main() {
    /// d) Test the synchronised queue by creating producer and consumer threads.
    // The shared queue
    SynchronisedQueue<std::string> queue;

    // Create producers
    Producer p(1, &queue);
    std::thread p1(p);

    // Create consumer
    Consumer c(1, &queue);
    std::thread c1(c);

    // interupt the threads
    join(p1);
    join(c1);
}