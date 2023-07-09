/*
    Level 4.2: STL Algorithms II
    Problem 2: Predicates for Ranges

    Name: Boyu Yang

    Problem objective:
    a) Apply the other three algorithms to this container while experimenting with various binary predicate arguments.
    b) Test the efficiency of the code in this question.

*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <execution> // parallel extention in C++ 20 
#include <chrono>
#include <functional>
#include <random>

using Vector = std::vector<double>;

// Simple function that measures processing time of a function, use variadic template to pass function parameters
template <typename TFunc, typename... Args> void RunAndMeasure(const char* title, TFunc func, Args... args) {
    const auto start = std::chrono::steady_clock::now();
    auto ret = func(args...); // pass the parameter pack
    const auto end = std::chrono::steady_clock::now();
    std::cout << title << ": " << std::chrono::duration<double, std::milli>(end - start).count() << " ms, res " << ret << std::endl;
}

int main() {
    /// a) Apply the other three algorithms to this container while experimenting with various binary predicate arguments.
    Vector vec8{ 1.0, 2.0, 3.0, -4, 10.0 }; // Not ordered
    std::cout << std::boolalpha;
    // Method 1: is_sorted_until, return true if sorted
    auto isSortedUntil = [](const Vector& v) {return std::is_sorted_until(v.begin(), v.end()) == v.end(); };
    // Method 2: is_sorted, return true is sorted ascending order
    auto isSorted = [](const Vector& v) {return std::is_sorted(v.begin(), v.end(), std::less<double>()); }; // test ascending or not
    // Method 3: adjacent_find with defined comparator. It finds the first two adjacent values that satisfy the comparator
    // we use std::greater so it returns the first place where two adjacent values violate ascending order
    auto adjFind = [](const Vector& v) {return std::adjacent_find(v.begin(), v.end(), std::greater<double>()) == v.end(); }; // test ascending or not
    
    // test efficiency
    RunAndMeasure("is_sorted_until", isSortedUntil, vec8);
    RunAndMeasure("is_sorted", isSorted, vec8);
    RunAndMeasure("adjacent_find", adjFind, vec8);
    

    /// b) Test the efficiency of the code in this question.
    // we now create a large random vector to test efficiency
    // generate uniform distribution with given random seed
    std::mt19937 gen(34);
    std::uniform_real_distribution<double> dist(1, 10000);

    // generate a vector with length 100000
    std::vector<double> randomVector;
    randomVector.reserve(100000); 
    // generate random vector with partial order
    for (int i = 0; i < 100000; ++i) {
        randomVector.push_back(i + 1);
    }
    for (int i = 1000; i < 100000; ++i) {
        int randomNum = dist(gen);
        randomVector.push_back(randomNum);
    }

    // test efficiency
    RunAndMeasure("is_sorted_until", isSortedUntil, randomVector);
    RunAndMeasure("is_sorted", isSorted, randomVector);
    RunAndMeasure("adjacent_find", adjFind, randomVector);

    // conclusion: for small sized arrays, "is_sorted" and "adjacent_find" are faster than "is_sorted_until", because "is_sorted" 
    // does not need to track the index where the sorting is violated. For large sized arrays, "adjacent_find" is 
    // fastest, "is_sorted" however is slower than "is_sorted_until" possibly because "adjacent_find" and "is_sorted_until"
    // stop once the violation is found, while "is_sorted" need to manipulate the whole vector.

}
