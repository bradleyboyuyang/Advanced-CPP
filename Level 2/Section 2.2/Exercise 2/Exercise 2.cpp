/*
    Level 2.2: Advanced Type Traits
    Problem 2: Arrays Categories

    Name: Boyu Yang

    Problem objective:
    We discuss some functions that work with array types. The rank of an array type is equal to the number of 
    dimensions of the array. The extent of an array type is the number of elements along the Nth dimension of 
    the array if N is in the closed interval [0, std::rank<T>::value]. For any other type, the value is 0.
    Answer the following questions:
    a) Test std::is_array() on a range of fundamental, scalar, object, arithmetic and compound types.
    b) Create an array int [][3][4][5]. Find its rank and extent.
    c) Call std::remove_extent() and std::remove_all_extent() on the array in question b). What is happening?

*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <type_traits>

int main()
{
    /// Part (A) Test std::is_array() on a range of fundamental, scalar, object, arithmetic and compound types.
    // fundamental types
    std::cout << "Fundamental types: " << std::endl;
    std::cout << "void: " << std::is_array<void>::value << std::endl;
    std::cout << "int: " << std::is_array<int>::value << std::endl;
    std::cout << "nullptr_t: " << std::is_array<std::nullptr_t>::value << std::endl;

    // scalar types
    std::cout << "Scalar types: " << std::endl;
    enum Suit {SPADE, HEART, DIAMOND, CLUB};
    std::cout << "double: " << std::is_array<double>::value << std::endl;         
    std::cout << "enum: " << std::is_array<Suit>::value << std::endl;
    std::cout << "nullptr: " << std::is_array<decltype(nullptr)>::value << std::endl;

    // arithmetic types
    std::cout << "Arithmetic types: " << std::endl;
    std::cout << "bool: " << std::is_array<bool>::value << std::endl;
    std::cout << "float: " << std::is_array<float>::value << std::endl;
    std::cout << "char const: " << std::is_array<char const>::value << std::endl;
    
    // object types
    std::cout << "Object types: " << std::endl;
    std::cout << "string: " << std::is_array<std::string>::value << std::endl;
    std::cout << "int pointer: " << std::is_array<int*>::value << std::endl;
    std::cout << "array: " << std::is_array<float[5]>::value << std::endl;

    // compound types
    std::cout << "Compound types: " << std::endl;
    std::cout << "vector: " << std::is_array<std::vector<int>>::value << std::endl;
    std::cout << "int reference: " << std::is_array<int&>::value << std::endl;
    std::cout << "int pointer: " << std::is_array<int*>::value << std::endl;
    std::cout << "array pointer: " << std::is_array<std::array<int, 2>*>::value << std::endl;
    std::cout << "array reference: " << std::is_array<std::array<int, 2>&>::value << std::endl;
    std::cout << "high dimention array: " << std::is_array<int[3][5][4]>::value << std::endl;

    /// Part (B) Create an array int [][3][4][5]. Find its rank and extent
    std::cout << "Rank: " << std::rank<int [][3][4][5]>::value << std::endl; 
    std::cout << "Extent 0: " << std::extent<int [][3][4][5], 0>::value << std::endl;  
    std::cout << "Extent 1: " << std::extent<int [][3][4][5], 1>::value << std::endl;  
    std::cout << "Extent 2: " << std::extent<int [][3][4][5], 2>::value << std::endl; 
    std::cout << "Extent 3: " << std::extent<int [][3][4][5], 3>::value << std::endl; 


    /// Part (C) Call std::remove_extent() and std::remove_all_extent() on the array in question b). What is happening?
    // remove extent
    using typeA = std::remove_extent<int[][3][4][5]>::type;
    std::cout << "Underlying type after remove_extent: " << typeid(typeA).name() << '\n';
    using typeB = std::remove_all_extents<int[][3][4][5]>::type;
    std::cout << "Underlying type after remove_all_extents: " << typeid(typeB).name() << '\n';

    std::cout << "Rank after remove_extent: " << std::rank<typeA>::value << std::endl;
    std::cout << "Extent 0 after remove_extent: " << std::extent<typeA, 0>::value << std::endl;
    std::cout << "Extent 1 after remove_extent: " << std::extent<typeA, 1>::value << std::endl;
    std::cout << "Extent 2 after remove_extent: " << std::extent<typeA, 2>::value << std::endl;

    std::cout << "Rank after remove_all_extents: " << std::rank<typeB>::value << std::endl;

}


