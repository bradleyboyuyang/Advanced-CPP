/*
    Level 2.5, 2.6: IEEE 754 and C Floating Point Classification
    Problem 3: Machine Precision Issues

    Name: Boyu Yang

    Problem objective:
    This exercise requires that you do some research into how C++ 11 and Boost C++ Math Toolkit supports
    the following functionality (x is a given value):
    • The next representable value that is greater than x. An overflow_error is thrown if no such value
    exists (float_next).
    • The next representable value that is less than x. An overflow_error is thrown if no such value exists
    (float_prior).
    • Advance a floating-point number by a specified number of ULP (Unit in Last Place) (float_advance).
    • Find the number of gaps/bits/ULP between two floating-point value (float_distance).
    • (C++11 and Boost) Return the next representable value of x in the direction y
    (std/boost::nextafter(x,y)).

*/

#include <iostream>
#include <cmath>
#include <boost/math/special_functions/next.hpp>

int main() {
    /// Check how C++ 11 and Boost C++ Math Toolkit supports the following functionality
    /// The next representable value that is greater than x. An overflow_error is thrown if no such value exists(float_next)
    // Boost uses boost::math::float_next; STL use nextafter to get the same result
    float f1 = 1e-20;
    std::cout << "(Boost) Next representable value that is greater than " << f1 << ": " << boost::math::float_next(f1) << std::endl;
    std::cout << "(STL) Next representable value that is greater than " << f1 << ": " << std::nextafter(f1, std::numeric_limits<float>::infinity()) << std::endl;

    std::cout << "(Boost) Next representable value that is greater than STL minimum" << ": " << boost::math::float_next(std::numeric_limits<float>::min()) << std::endl;
    std::cout << "(STL) Next representable value that is greater than STL minimum" << ": " << std::nextafter(std::numeric_limits<float>::min(), std::numeric_limits<float>::infinity()) << std::endl;

    /// The next representable value that is less than x. An overflow_error is thrown if no such value exists (float_prior).
    // Boost uses boost::math::float_next; STL can still use nextafter to get the same result, with a negative sign
    std::cout << "(Boost) Next representable value that is less than " << f1 << ": " << boost::math::float_prior(f1) << std::endl;
    std::cout << "(STL) Next representable value that is less than " << f1 << ": " << std::nextafter(f1, -std::numeric_limits<float>::infinity()) << std::endl;

    std::cout << "(Boost) Next representable value that is less than STL maximum" << ": " << boost::math::float_prior(std::numeric_limits<float>::max()) << std::endl;
    std::cout << "(STL) Next representable value that is less than STL maximum" << ": " << std::nextafter(std::numeric_limits<float>::max(), -std::numeric_limits<float>::infinity()) << std::endl;


    /// Advance a floating-point number by a specified number of ULP (Unit in Last Place) (float_advance).
    // Use STL algorithms: repeatedly use nextafter to achieve the specified number of ULP
    float z = 1.1;
    int ulp = 200; // number of ULP
    int ulp2 = -30000;
    // Use boost::math::float_advance
    std::cout << "Advance " << z << " by " << ulp << " ULP: " << boost::math::float_advance(z, ulp) << std::endl;
    std::cout << "Advance " << z << " by " << -ulp << " ULP: " << boost::math::float_advance(z, -ulp) << std::endl;
    std::cout << "Advance " << z << " by " << ulp2 << " ULP: " << boost::math::float_advance(z, ulp2) << std::endl;
    std::cout << "Advance " << z << " by " << -ulp2 << " ULP: " << boost::math::float_advance(z, -ulp2) << std::endl;

    /// Find the number of gaps/bits/ULP between two floating-point value (float_distance).
    // Number gaps/bits/ULP between 2 floating-point values a and b
    // Returns a signed value indicating whether a < b
    double a = 0.1; double b = a + std::numeric_limits<float>::min();
    std::cout << boost::math::float_distance(a, b) << std::endl;
    std::cout << boost::math::float_distance(1.0, 0.0) << std::endl;
    std::cout << boost::math::float_distance(0.0, 0.5) << std::endl;

    /// (C++11 and Boost) Return the next representable value of x in the direction y (std / boost::nextafter(x, y)).
    float f = 1.111;
    float next_stl = std::nextafter(f, std::numeric_limits<float>::max());
    std::cout << "(STL) Next representable value greater than " << f << ": " << next_stl << std::endl;
    float next_boost = boost::math::nextafter(f, std::numeric_limits<float>::max());
    std::cout << "(Boost) Next representable value greater than " << f << ": " << next_boost << std::endl;

}