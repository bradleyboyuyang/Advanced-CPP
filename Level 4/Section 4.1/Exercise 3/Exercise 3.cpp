/*
    Level 4.1: STL Algorithms I
    Problem 3: Compile-Time Matrix Class

    Name: Boyu Yang

    Problem objective:
    This exercise is similar in structure to exercise 2 except that we now wish to create a compile-time matrix class:
    Constructors: default, with value as argument and copy constructor.
    Accessing elements (read/write) using (,).
    Adding and subtraction; unary minus.
    Premultiplication by a scalar quantity
    a) Given the above operations to be implemented you need to choose a suitable data structure ADT to hold the data
    The choice depends on how efficient the ADT is and how much functionality can be delegated to the ADT.
    b) Execute the equivalent of the steps b) to e) from exercise 2 but you now do it for matrices instead of vectors.
*/

#include "Matrix.hpp"

int main() {
    // Creating matrices
    Matrix<double, 2, 3> A; // default constructor
    Matrix<double, 2, 3> B(2);  // value constructor
    Matrix<double, 2, 3> C(B);  // Copy constructor
    std::cout << "A:\n" << A << std::endl;
    std::cout << "B:\n" << B << std::endl;
    std::cout << "C:\n" << C << std::endl;

    // Accessing elements
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    std::cout << "A modified:\n" << A << std::endl;

    // Addition
    std::cout << "A+B:\n" << A+B << std::endl;
     //Subtraction
    std::cout << "A-B:\n" << A - B << std::endl;
    // Unary minus
    std::cout << "-A:\n" << -A << std::endl;
    // Premultiplication by a scalar
    std::cout << "3.14 * A:\n" << 3.14 * A << std::endl;
    // premultiplication by any type
    long long a = 4;
    std::cout << "a (long long) * A:\n" << a * A << std::endl;
    // test modify
    A.modify([](auto& x) { return x + 1; });  // Increment all elements by 1
    std::cout << "A after modification: \n";
    std::cout << A << std::endl;

}