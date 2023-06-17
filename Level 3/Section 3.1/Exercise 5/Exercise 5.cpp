/*
    Level 3.1: Threads
    Problem 5: Atomics and Atomic Operations 101

    Name: Boyu Yang

    File: Exercise 4.cpp
    Description: Main file for execution

    Problem objective:
    a) Create atomic objects of type long long, bool and int.
    b) Determine which atomic types are lock-free.
    c) Atomically replace the value of one atomic object by another atomic object.
    d) Atomically load an atomic object and return its current value.

*/

#include <iostream>
#include <atomic>

int main() {
    /// a) Create atomic objects of type long long, booland int.
    std::atomic_llong v1(2);
    std::atomic_bool v2(true);
    std::atomic_int v3(4);
    std::cout << std::boolalpha;
    std::cout << "Value v1, v2, v3: " << v1 << ", " << v2 << ", " << v3 << std::endl; // 2, true, 4
    
    /// b) Determine which atomic types are lock-free.
    // Lock-free ADT means more than 1 thread can access it concurrently
    std::cout << "Atomic long long Lock-free: " << v1.is_lock_free() << std::endl;
    std::cout << "Atomic bool Lock-free: " << v2.is_lock_free() << std::endl;
    std::cout << "Atomic int Lock-free: " << v3.is_lock_free() << std::endl;
    
    /// c) Atomically replace the value of one atomic object by another atomic object.
    v1.store(std::atomic_long{ 123 }); // use store() to automically replace the value
    std::cout << "Value v1, v2, v3: " << v1 << ", " << v2 << ", " << v3 << std::endl; // 123, true, 4

    /// d) Atomically load an atomic object and return its current value.
    std::cout << "Value v1, v2, v3: " << v1.load() << ", " << v2.load() << ", " << v3.load() << std::endl; // 123, true, 4
}