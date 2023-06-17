/*
    Level 3.5: Complexity and STL Containers
    Problem 7: Compile-Time Fractional Arithmetic 101

    Name: Boyu Yang

    Problem objective:
    This exercise is based on std::ratio, a class template that supports rational arithmetic. It reduces the
    risk of run-time overflow because a ratio and any ratios resulting from ratio arithmetic are always reduced
    to the lowest terms.
    Answer the following questions:
    a) Create a number of instances of std::ratio and print them.
    b) Create two std::ratio instances; add, subtract, multiply and divide them.
*/

#include <iostream>
#include <ratio>

int main() {
    /// a) Create a number of instances of std::ratio and print them.
    std::cout << "Instances of std::ratio:" << std::endl;
    std::cout << std::ratio<1, 2>::num << "/" << std::ratio<1, 2>::den << std::endl;
    std::cout << std::ratio<3, 4>::num << "/" << std::ratio<3, 4>::den << std::endl;
    std::cout << std::ratio<5, 6>::num << "/" << std::ratio<5, 6>::den << std::endl;
    std::cout << std::ratio<7, 8>::num << "/" << std::ratio<7, 8>::den << std::endl;

    /// b) Create two std::ratio instances; add, subtract, multiplyand divide them.
    // use useful typedefs offered by standard library
    std::cout << "Operations on std::ratio:" << std::endl;
    using ratio1 = std::ratio<2, 30000>;
    // yocto, zepto, atto, femto, pico, nano, micro, milli, centi, deci...
    // reduce run-time overflow since ratio arithmetic are reduced to lowest terms
    using ratio2 = std::milli;
    // more convenient typedefs in https://en.cppreference.com/w/cpp/numeric/ratio/ratio

    // Addition
    using addition = std::ratio_add<ratio1, ratio2>;
    std::cout << "Addition: " << addition::num << "/" << addition::den << std::endl;

    // Subtraction
    using subtraction = std::ratio_subtract<ratio1, ratio2>;
    std::cout << "Subtraction: " << subtraction::num << "/" << subtraction::den << std::endl;

    // Multiplication
    using multiplication = std::ratio_multiply<ratio1, ratio2>;
    std::cout << "Multiplication: " << multiplication::num << "/" << multiplication::den << std::endl;

    // Division
    using division = std::ratio_divide<ratio1, ratio2>;
    std::cout << "Division: " << division::num << "/" << division::den << std::endl;

}
