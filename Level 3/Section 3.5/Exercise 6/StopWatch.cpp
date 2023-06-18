/*
    Level 3.5: Complexity and STL Containers
    Problem 6: std::chrono

    Name: Boyu Yang

    File: StopWatch.cpp
    Description: Adapter class implementation
*/

#include "StopWatch.hpp"

/// a) Implement an adapter class with the following interface
// default constructor
StopWatch::StopWatch(){}

// start the clock
void StopWatch::StartStopWatch() {
    start = std::chrono::steady_clock::now();
}

// end the clock
void StopWatch::StopStopWatch() {
    end = std::chrono::steady_clock::now();
}

// get the time passed
double StopWatch::GetTime() const {
    std::chrono::duration<double> duration{ end - start };
    return duration.count();
}


// reset the clock 
void StopWatch::Reset() {
    start = std::chrono::steady_clock::now();
    end = start; // we use the private reloaded assignment operator
}

// private copy constructor as required
StopWatch::StopWatch(const StopWatch& copy) {
    start = copy.start;
    end = copy.end;
}

// private assignment operator
StopWatch& StopWatch::operator=(const StopWatch& copy) {
    // we use the private reloaded copy constructor, both have const specifier
    StopWatch copyWatch(copy);
    return copyWatch;
}