/*
    File: Command.hpp
    Description: Class implementation for Command
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <thread>
#include <functional>

// given class
using FunctionType = std::function<double(double)>;
class Command
{
private:
    long ID; // priority of command
    FunctionType algo;
public:
    Command(const FunctionType& algorithm, long priority) : algo(algorithm), ID(priority) {}
    void Execute(double x)
    {
        // Introduce delay to simulate a heavy algorithm
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << algo(x) << '\n';
    }
    int priority() const
    {
        return ID;
    }
};