/*
    Level 2.5, 2.6: IEEE 754 and C Floating Point Classification
    Problem 1: Classifying Numbers

    Name: Boyu Yang

    Problem objective:
    In this exercise we use C++11 syntax to categorise float, double, long double and integral types as 
    zero, subnormal, normal, infinite, NaN or an implementation-defined category.
    To this end, employ std::fpclassify() as used in the template function.

    a) Test the given function for the following values (in other words, determine the category)
    b) Apply the functions std::isfinite, std::isinf, std::isnan, std::isnormal to the given values

*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

// Given function to classify different types into normal, NaN, Inf, subnormal, zero, unknown
template <typename T>
const char* Classify(T t)
{
    switch (std::fpclassify(t))
    {
    case FP_INFINITE: return "Inf";
    case FP_NAN: return "NaN";
    case FP_NORMAL: return "normal";
    case FP_SUBNORMAL: return "subnormal";
    case FP_ZERO: return "zero";
    default: return "unknown";
    }
}

int main() {
    /// Part (A) Test the given function for the following values (in other words, determine the category) 
    double val = std::numeric_limits<double>::max();
    std::cout << Classify<double>(val) << std::endl; // normal
    std::cout << Classify<double>(2*val) << std::endl; // Inf
    std::cout << Classify<double>(val + 3.1415) << std::endl;// normal

    double val2 = std::numeric_limits<double>::min() - 3.1415; 
    std::cout << Classify<double>(val2) << std::endl; // normal
    std::cout << Classify<double>(val2/2.0) << std::endl; // normal
    std::cout << Classify<double>(DBL_MIN / 2) << std::endl; // subnormal

    /// Part (B) Apply the functions std::isfinite, std::isinf, std::isnan, std::isnormal to the given values
    double factor = 2.0;
    val = factor * std::numeric_limits<double>::max(); // infinity

    // val: infinite
    std::cout << "val is finite " << std::boolalpha << std::isfinite(val) << std::endl; // false
    std::cout << "val is infinite " << std::boolalpha << std::isinf(val) << std::endl; // true
    std::cout << "val is a nan " << std::boolalpha << std::isnan(val) << std::endl; // false
    std::cout << "val is normal " << std::boolalpha << std::isnormal(val) << std::endl; // false

    // val - val: illegal operations, resulting NaN
    std::cout << "val - val is finite " << std::boolalpha << std::isfinite(val - val) << std::endl; // false
    std::cout << "val - val is infinite " << std::boolalpha << std::isinf(val - val) << std::endl; // false
    std::cout << "val - val is a nan " << std::boolalpha << std::isnan(val - val) << std::endl; // true
    std::cout << "val - val is normal " << std::boolalpha << std::isnormal(val - val) << std::endl; // false

    // std::sqrt(-1): illegal operations, resulting NaN
    std::cout << "std::sqrt(-1) is finite " << std::boolalpha << std::isfinite(std::sqrt(-1)) << std::endl; // false
    std::cout << "std::sqrt(-1) is infinite " << std::boolalpha << std::isinf(std::sqrt(-1)) << std::endl; // false
    std::cout << "std::sqrt(-1) is a nan " << std::boolalpha << std::isnan(std::sqrt(-1)) << std::endl; // true
    std::cout << "std::sqrt(-1) is normal " << std::boolalpha << std::isnormal(std::sqrt(-1)) << std::endl; // false

    // std::log(0.0): infinite
    std::cout << "std::log(0.0) is finite " << std::boolalpha << std::isfinite(std::log(0.0)) << std::endl; // false
    std::cout << "std::log(0.0) is infinite " << std::boolalpha << std::isinf(std::log(0.0)) << std::endl; // true
    std::cout << "std::log(0.0) is a nan " << std::boolalpha << std::isnan(std::log(0.0)) << std::endl; // false
    std::cout << "std::log(0.0) is normal " << std::boolalpha << std::isnormal(std::log(0.0)) << std::endl; // false

    // std::exp(val): infinite
    std::cout << "std::exp(val) is finite " << std::boolalpha << std::isfinite(std::exp(val)) << std::endl; // false
    std::cout << "std::exp(val) is infinite " << std::boolalpha << std::isinf(std::exp(val)) << std::endl; // true
    std::cout << "std::exp(val) is a nan " << std::boolalpha << std::isnan(std::exp(val)) << std::endl; // false
    std::cout << "std::exp(val) is normal " << std::boolalpha << std::isnormal(std::exp(val)) << std::endl; // false
}