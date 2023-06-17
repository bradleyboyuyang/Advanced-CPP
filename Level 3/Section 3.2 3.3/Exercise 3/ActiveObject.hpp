/*
    Level 3.2 3.3: C++ Concurrency
    Problem 3: Active Objects 101

    Name: Boyu Yang

    File: ActiveObject.hpp
    Description: Adapter class implementation for ActiveObject
*/

# pragma once

#include <iostream>
#include <thread>

/// b) Create an active object based on a thread with no associated thread function.
// adapter class called ActiveObject that is composed of a thread
class ActiveObject {
private:
    // a reference to an instance of an std::thread instance
    std::thread thread;
    std::thread& thread_{thread};
public:
    ActiveObject() = default;
    // explicit constructor accepting a thread with associated thread function
    explicit ActiveObject(std::thread& new_thread) : thread_(new_thread) { std::cout << "call explicit constructor\n"; };

    // destructor
    ~ActiveObject() {
        if (thread_.joinable())
            thread_.join();
        std::cout << "call destructor" << std::endl;
    }
};