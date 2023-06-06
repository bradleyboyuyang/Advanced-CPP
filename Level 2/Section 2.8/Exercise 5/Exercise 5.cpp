/*
    Level 2.8: STL Bitset and Boost Dynamic Bitset
    Problem 5: std::vector<bool> versus Bitset
	Exercise 5.cpp: main execution file
    Name: Boyu Yang

    Problem objective:
    Create a compile-time matrix (call it BitMatrix<N, M>) consisting of N rows and M:
    columns whose elements are bits. Some requirements are:
    a) Determine which data structure to use in order to implement BitMatrix<N, M>, for example as a
    nested array std::array<std::bitset<M>, N> or a one-dimensional array std::bitset<N*M>.
    Which choice is “optimal” is for you to decide.
    b) Constructors need to be created. Use the same defaults as with std::bitset<M>.
    c) Implement the following for all rows in the matrix and for a given row in the matrix:
    • Set/reset all bits.
    • Flip the bits.
    • Test if none, all or any bits are set.
    • Access the elements.
    • Count the number of set bits.
    d) Create member functions for OR, XOR and AND Boolean operations on bit matrices.
*/

#include "BitMatrix.hpp"

int main() {

    /// a) Determine which data structure to use in order to implement BitMatrix<N, M>, for example as a
    /// nested array std::array<std::bitset<M>, N> or a one-dimensional array std::bitset<N*M>.
    /// Which choice is “optimal” is for you to decide.
    // A nested array provides effcient access to individual bits in the matrix. 
    // It also allows for row-wise operations and access on the matrix, compared with one-dimensional array.
    // Therefore we consider the nested array as the "optimal" choice regarding the balance between efficiency and ease of use.

    /// b) Constructors need to be created. Use the same defaults as with std::bitset<M>.
    // The implemented class is defined in "BitMatrix.cpp". We test the constructor below:
    
	BitMatrix<5, 3> bitmatrix;
	std::cout << "printing constructor: ";
	bitmatrix.print(); // printing results 

	// testing constructor with value input 
	BitMatrix<5, 6> bitmatrix1(9);
	std::cout << "printing constructor with value input: ";
	bitmatrix1.print();

	// testing copy constructor 
	auto bitmatrix2(bitmatrix1);
	std::cout << "printing copy constructor: ";
	bitmatrix2.print();

	// testing move constructor 
	auto bitmatrix3(std::move(bitmatrix2)); //Move constructor
	bitmatrix3.print();

    /// c) Implement the following for all rows in the matrix and for a given row in the matrix:
    /// Set/reset all bits; Flip the bits; Test if none, all or any bits are set; Access the elements; Count the number of set bits.
    // The implemented class is defined in "BitMatrix.cpp". We test the row operations below:

	// test if none, all or any bits are set 
	std::cout << "Checking if bits are set " << bitmatrix3.all() << std::endl;
	std::cout << "Checking if no bits are set " << bitmatrix3.none() << std::endl;
	std::cout << "Checking if any bits are set " << bitmatrix3.any() << std::endl;

	// access the elements 
	std::size_t x = 4;
	std::size_t y = 5;
	bitmatrix3.print();
	std::cout << "Checking access to (4,5) " << bitmatrix3(x, y) << std::endl;
	std::cout << "Counting number of elements in row 2 " << bitmatrix3.count(2) << std::endl;
	std::cout << "Counting total elements " << bitmatrix3.count() << std::endl;

    /// d) Create member functions for OR, XOR and AND Boolean operations on bit matrices.
    // The implemented class is defined in "BitMatrix.cpp". We test the bitwise operations below:

	std::cout << "Testing bitwise operations" << std::endl;
	std::cout << "Testing bitwise operation XOR" << std::endl;
	BitMatrix<5, 6> bitmatrix4 = bitmatrix3 ^ bitmatrix2;
	bitmatrix4.print();

	// bitmatrix 4,5,6 all have to be the same size 
	std::cout << "Testing bitwise operation OR" << std::endl;
	BitMatrix<5, 6> bitmatrix5 = (bitmatrix4 | bitmatrix2);
	bitmatrix5.print();
	std::cout << "Testing bitwise operation AND" << std::endl;
	BitMatrix<5, 6> bitmatrix6 = bitmatrix4 & bitmatrix2;
	bitmatrix6.print();


}