/*
    Level 4.1: STL Algorithms I
    Problem 2: Compile-Time Vector Class

    Name: Boyu Yang

    Problem objective:
    In the next two exercises we create fixed-sized vector and matrix classes, that is classes whose instances
    reside on the stack rather than on the heap. There are many applications of these classes where there is a
    need for tiny vectors and tiny matrices. The scope and requirements for both classes are:
    Constructors: default, with value as argument and copy constructor.
    Accessing elements (read/write) using [].
    Adding and subtraction; unary minus.
    Premultiplication by a scalar quantity.

    a) Given the above operations to be implemented you need to choose a suitable data structure ADT to hold the data
    The choice depends on how efficient the ADT is and how much functionality can be delegated to the ADT.
    b) Create some instances of Vector and print them.
    c) Implement the above operation pertaining to the properties of a vector space as explained in the introduction.
    d) Implement the scalar multiplication operation as a template member function having an extra template parameter
    e) Create a member function that modifies all the elements of a vector using std::function <T(const T&)>. 
    Internally, the member function should call std::transform or use the internal array
    directly. Be careful: data is on the stack and not on the heap.
*/

#include <iostream>
#include "Vector.hpp"

int main() {
    /// b) Create some instances of Vector and print them
    Vector<double, 3> vec1(std::array<double, 3>{1, 2, 3});
    std::cout << vec1 << std::endl;
    Vector<double, 3> vec2(std::array<double, 3>{4, 5, 6});
    std::cout << vec2 << std::endl;

    /// c) Test code
    Vector<double, 3> vec3(vec1);
    std::cout << vec1 + vec2 << std::endl;
    std::cout << vec1 - vec2 << std::endl;
    std::cout << -vec1 << std::endl;
    double pi{ 3.14 };
    // test premultiplication
    std::cout << pi * vec1 << std::endl;

    /// d) Test code
    Vector<float, 3> v1(2.3);  // Vector [1, 1, 1]
    std::cout << 3.14 * v1 << std::endl;
    // we see this now works for all types

    /// e) Test code
    v1.modify([](auto& x) { return x*(x+3); });  // Increment all elements by 1

    std::cout << "v1 after modification: ";
    std::cout << v1 << std::endl;
}