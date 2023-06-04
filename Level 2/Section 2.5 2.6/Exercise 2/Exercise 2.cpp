/*
    Level 2.5, 2.6: IEEE 754 and C Floating Point Classification
    Problem 2: Machine Epsilon

    Name: Boyu Yang

    Problem objective:
    Machine epsilon gives an upper bound on the relative error due to rounding in floating point arithmetic. In 
    C++11, epsilon is the difference between 1.0 and the next representable value of the given floating-point type. 
    a) Write a small C function to compute epsilon. Generalise this function for other types
    b) Compare the value from part a) with the value produced by std::numeric_limits<double>::epsilon().

*/

#include <iostream>
#include <cmath>

/// Part (A) Write a small C function to compute epsilon. Generalise this function for other types
// We use template parameter combined with explicit type conversion to generalize the given function
// The principle is to divide the epsilon until the system thinks it is trivial enough
template <typename T>
T calcEpsilon() {
    T epsilon = (T)1.0;
    while ((T)1.0 + (T)0.5 * epsilon != (T)1.0) {
        epsilon *= (T)0.5;
    }
    return epsilon;
}


int main() {
    /// Part (B) Compare the value from part a) with the value produced by std::numeric_limits<double>::epsilon().
    // float
    std::cout << calcEpsilon<float>() << std::endl;
    std::cout << std::numeric_limits<float>::epsilon() << std::endl;
    std::cout << "Whether the computed and built-in epsilon are the same: " << std::boolalpha << (calcEpsilon<float>() == std::numeric_limits<float>::epsilon()) << std::endl;

    // double
    std::cout << calcEpsilon<double>() << std::endl;
    std::cout << std::numeric_limits<double>::epsilon() << std::endl;
    std::cout << "Whether the computed and built-in epsilon are the same: " << std::boolalpha << (calcEpsilon<double>() == std::numeric_limits<double>::epsilon()) << std::endl;

    // long double
    std::cout << calcEpsilon<long double>() << std::endl;
    std::cout << std::numeric_limits<long double>::epsilon() << std::endl;
    std::cout << "Whether the computed and built-in epsilon are the same: " << std::boolalpha << (calcEpsilon<long double>() == std::numeric_limits<long double>::epsilon()) << std::endl;

}