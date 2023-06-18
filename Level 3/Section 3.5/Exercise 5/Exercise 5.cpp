/*
    Level 3.5: Complexity and STL Containers
    Problem 4: Synchronising Queue

    Name: Boyu Yang

    Problem objective:
    We now generalise exercise 2 to accomodate multiple concurrent producers and consumers of
    commands. First, implement the solution in Boost and then migrate it to C++11.
    Answer the following questions:
    a) Create a thread group for producers and add commands to it.
    b) Create a thread group for consumers and add commands to it.
    c) Start the application; we need to know when to stop processing and to this end we define a special
    command object that can be recognized by consumers to let them know that there is no more input.
    (In general, we could use libraries such as Microsoft’s PPL and Intel’s TBB that have support for concurrent
    containers. These libraries are outside the scope of the current course).

*/

#include <thread>
#include "Consumer.hpp"
#include "Producer.hpp"
#include "Command.hpp"


int main() {
    /// a) Create a thread group for producers and add commands to it.
    /// b) Create a thread group for consumers and add commands to it.
    // number of producers and consumers
    const int nrProducers = 3, nrConsumers = 3;

    // define the comparator as in exercise 2
    // The comparator means that Command instances with smaller values have higher priority.
    auto comparator = [](const Command& a, const Command& b) {return a.priority() > b.priority(); };
    
    // The shared queue (use C++ 20 and above otherwise require priority_queue(comparator))
    SynchronisedQueue <Command, std::vector<Command>, decltype(comparator)> queue;

    // Create thread group for producers
    // In boost we can use boost::thread_group, while in STL will create a list of threads
    std::thread producers[nrProducers];
    
    for (int i = 0; i < nrProducers; i++)
    {
        Producer p(i, &queue);

        // determine whether a special command object
        // here we let the command (id=0) be the special Command object, meaning that the producer will only produce once
        // and the consumer can recognize the special Command object and then know that there is no more input and hence stop dequeue
        bool flag = false;
        if (i == 0)
            flag = true;

        // create command instances with index as its priority and the flag
        Command c([](double x) { return x * x; }, i, flag);
        producers[i] = std::thread(p, c);
    }

    // Create thread group for consumers
    std::thread consumers[nrConsumers];
    for (int i = 0; i < nrConsumers; i++)
    {
        Consumer c(i, &queue);
        consumers[i] = std::thread(c);
    }

    /// c) Start the application; we need to know when to stop processingand to this end we define a special
    /// command object that can be recognized by consumers to let them know that there is no more input.
    // Interrupt the threads and stop them
    for (auto& producer : producers) { producer.join(); };
    for (auto& consumer : consumers) { consumer.join(); };

    // We can see that all non-special Command objects (id > 0) keep being produced and consumed, while the special 
    // Command object (id=0) stop consuming after recognizing there is no more producing.
}

