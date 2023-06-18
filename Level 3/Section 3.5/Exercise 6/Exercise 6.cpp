/*
    Level 3.5: Complexity and STL Containers
    Problem 6: std::chrono

    Name: Boyu Yang

    File: Exercise6.cpp
    Description: Client program

    Problem objective:
    In this exercise we create an adapter class for certain functionality in the std::chrono library. The
    objective is to create a class to measure how long it takes for an operation to complete.

*/

#include <thread>
#include <random>

#include "StopWatch.hpp"

int main() {
    /// b) test the class
    StopWatch stopwatch;

    // start watch
    stopwatch.StartStopWatch();

    // Simulate some time-consuming operation
    std::default_random_engine dre;
    std::uniform_int_distribution<int> delay(200, 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay(dre)));

    // stop watch
    stopwatch.StopStopWatch();

    // get the time elapsed
    std::cout << "Elapsed time: " << stopwatch.GetTime() << " seconds" << std::endl;

    // reset the watch
    stopwatch.Reset();
    // now getTime should be 0
    std::cout << "Elapsed time: " << stopwatch.GetTime() << " seconds" << std::endl;

}
