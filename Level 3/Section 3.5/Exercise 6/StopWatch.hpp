/*
    Level 3.5: Complexity and STL Containers
    Problem 6: std::chrono

    Name: Boyu Yang

    File: StopWatch.hpp
    Description: Adapter class prototype/interface
*/

#pragma once

#include <iostream>
#include <chrono>

/// a) Implement an adapter class with the following interface
class StopWatch
{
public:
    StopWatch(); // default constructor
    void StartStopWatch(); // start timing
    void StopStopWatch(); // end timing
    void Reset(); // reset the clock
    double GetTime() const; // get the elpased time
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    StopWatch(const StopWatch&);
    StopWatch& operator=(const StopWatch&);
};
