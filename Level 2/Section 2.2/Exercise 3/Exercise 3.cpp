/*
    Level 2.2: Advanced Type Traits
    Problem 3: Conversions

    Name: Boyu Yang

    Problem objective:
    Sometimes you may wish to structurally change fundamental properties of types in an application.
    Examples are:
    • Mapping integers to unsigned integers and vice versa.
    • Add/remove the const specifier to or from a type.
    • Add/remove a pointer to or from a type.
    • Add/remove the volatile specifier to or from a type.
    • Discuss the difference between direct list initialisation and copy list initialisation in C++17/20
    compared to C++11. In which case does auto deduction reduce to std::initializer_list?
    Give a code example. Under which circumstances can we get ill-formed expressions?
    • Discuss how Class Template Argument Deduction (CTAD)) reduces code verbosity. Give a non-trivial
    example using std::tuple and a user-defined class.
    • Investigate the applicability of decltype and std::is_same when comparing the type of a result with a
    “target” type.
    Answer the following questions:
    a) Write a separate function for each of the above requirements.
    b) Test the functions on a range of fundamental, scalar, object, arithmetic and compound types.

*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>



int main()
{
    /// Part (A) 
    /// Part (B) Test the functions on a range of fundamental, scalar, object, arithmetic and compound types
    // fundamental types

    unsigned int a = 123;
    signed int b = -123;
    std::cout << "Signed to unsigned: " << mapInteger()
        std::cout << mapInteger(b);

    //std::cout << "Fundamental types: " << std::endl;
    //std::cout << "void: " << std::is_array<void>::value << std::endl;
    //std::cout << "int: " << std::is_array<int>::value << std::endl;
    //std::cout << "nullptr_t: " << std::is_array<std::nullptr_t>::value << std::endl;

    //// scalar types
    //std::cout << "Scalar types: " << std::endl;
    //enum Suit { SPADE, HEART, DIAMOND, CLUB };
    //std::cout << "double: " << std::is_array<double>::value << std::endl;
    //std::cout << "enum: " << std::is_array<Suit>::value << std::endl;
    //std::cout << "nullptr: " << std::is_array<decltype(nullptr)>::value << std::endl;

    //// arithmetic types
    //std::cout << "Arithmetic types: " << std::endl;
    //std::cout << "bool: " << std::is_array<bool>::value << std::endl;
    //std::cout << "float: " << std::is_array<float>::value << std::endl;
    //std::cout << "char const: " << std::is_array<char const>::value << std::endl;

    //// object types
    //std::cout << "Object types: " << std::endl;
    //std::cout << "string: " << std::is_array<std::string>::value << std::endl;
    //std::cout << "int pointer: " << std::is_array<int*>::value << std::endl;
    //std::cout << "array: " << std::is_array<float[5]>::value << std::endl;

    //// compound types
    //std::cout << "Compound types: " << std::endl;
    //std::cout << "vector: " << std::is_array<std::vector<int>>::value << std::endl;
    //std::cout << "int reference: " << std::is_array<int&>::value << std::endl;
    //std::cout << "int pointer: " << std::is_array<int*>::value << std::endl;
    //std::cout << "array pointer: " << std::is_array<std::array<int, 2>*>::value << std::endl;
    //std::cout << "array reference: " << std::is_array<std::array<int, 2>&>::value << std::endl;
    //std::cout << "high dimention array: " << std::is_array<int[3][5][4]>::value << std::endl;
}