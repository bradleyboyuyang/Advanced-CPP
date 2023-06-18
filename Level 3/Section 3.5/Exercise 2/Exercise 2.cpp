/*
    Level 3.5: Complexity and STL Containers
    Problem 2: Simple Single-Threaded Command Processor Pattern

    Name: Boyu Yang

    Problem objective:
    In this exercise we create a mini-application. We generalise and extend it in Module 5. It is a single
    threaded producer-consumer pattern in which executable commands are inserted into a priority queue.
    When finished, consumer code executes each command in the priority queue in turn before popping it
    Answer the following questions:
    a) Create a comparator for Command to compare two of its instances.
    b) Create several instances of Command.
    c) Create a priority queue of commands and insert the objects from part b) into it.
    d) Execute each command in the priority queue until it is empty.

*/

#include <queue>
#include "Command.hpp"

int main() {
    /// a) Create a comparator for Command to compare two of its instances.
    auto comparator = [](Command a, Command b) {return a.priority() > b.priority(); };
    // The comparator means that Command instances with smaller values have higher priority.

    /// b) Create several instances of Command.
    FunctionType f = [](double x) {return x*x; }; // use function typedef
    // create instances
    Command c1(f, 3);
    Command c2(f, 1);
    Command c3(f, 2);
    
    /// c) Create a priority queue of commandsand insert the objects from part b) into it.
    std::priority_queue<Command, std::deque<Command>, decltype(comparator)> pQueue(comparator);
    pQueue.push(c1);
    pQueue.push(c2);
    pQueue.push(c3);

    /// d) Execute each command in the priority queue until it is empty.
    while (!pQueue.empty()) {
        auto top = pQueue.top();
        top.Execute(top.priority());
        pQueue.pop();
    }
    // The result is 1, 4, 9. According to our implementation, c2 has the highest priority, then c3, then c1.
    // Therefore we first pop c1, use Execute() to return the square of its ID, which is 1, then 4, then 9.
}