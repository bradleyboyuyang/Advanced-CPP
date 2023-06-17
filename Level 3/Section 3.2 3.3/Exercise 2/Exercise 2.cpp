/*
    Level 3.2 3.3: C++ Concurrency
    Problem 2: Smart Races with Smart Pointers

    Name: Boyu Yang

    Problem objective:
    simulate (undesirable) non-deterministic race conditions when multiple threads access functions that use shared pointers
    a) Create a function that accepts a smart pointer and a new value for its state
    The body should actually update the state and we should introduce enough latency (delay) in order to
    trigger a race condition; for example, you generate a uniform random number using C++ random
    library and then sleep for that amount of time.
    b) Create an array of 100 threads, fire each one up (each one has thread function Modify() and a given
    value that will be the new value of the instance of PointerType).
    c) Run the program a number of times; examine the output and explain what is happening.
*/

#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <algorithm>
#include <random>
#include <vector>

// same class in exercise 1
struct X {
    double val;

    X() : val(0.0) {}
    void operator()() { std::cout << "An X " << val << std::endl; }
};

// C++11
template <typename T>
using GenericPointerType = std::shared_ptr<T>;
using PointerType = GenericPointerType<X>;

std::mutex m;

/// a) Create a function that accepts a smart pointer and a new value for its state
// the desired function that introduces latency to trigger a race condition
void Modify(PointerType& p, double newVal)
{
    // Wait a while, long enough to trigger the race
    std::default_random_engine dre;
    std::uniform_int_distribution<int> delay(0, 100);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay(dre)));
    // change the value
    p->val = newVal;
    // we add a lock here not for synchronization but for a tidy console output
    m.lock();
    std::cout << "Value: " << p->val << std::endl;
    m.unlock();
}


int main() {
    /// b) Create an array of 100 threads, fire each one up (each one has thread function Modify() and a given
    /// value that will be the new value of the instance of PointerType).
    // initial shared pointer
    PointerType ptr(new X);
    ptr->val = 3.0; // initial value

    // Create an array of 100 threads
    std::thread threads[100];

    // Fire up each thread
    for (int i = 0; i < 100; i++)
    {
        // for each thread i we modify the value of the object through the shared pointer
        double newValue = static_cast<double>(i);
        threads[i] = std::thread(Modify, std::ref(ptr), newValue);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 100; i++)
    {
        threads[i].join();
    }

    // Print the final value
    std::cout << "Final value: " << ptr->val << std::endl;


    /// c) Run the program a number of times; examine the output and explain what is happening.
    // When running the program multiple times, we observe different outputs due to the non-deterministic nature of the race condition. 
    // A race condition occurs when multiple threads access and modify shared data concurrently, leading to undefined behavior. 
    // The random delay introduced in "Modify()" increase the likelihood of the race condition,
    // since different threads may finish sleeping and attempt to modify the state at different times.
    // Since there is no synchronization, the final value varies due to the race conditions.
    // If we move the "m.lock()" before changing the value "p->val = newVal;" we can get correct outputs
}


