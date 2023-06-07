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
    // The implemented class is defined in "BitMatrix.hpp". We test the constructor below:
    
	// default constructor
	BitMatrix<3, 4> matrix1; // Default constructor
	std::cout << "Default constructor:\n";
	matrix1.print();
	// constructor with all rows equal to the same value
	BitMatrix<2, 9> matrix2(123); 
	std::cout << "Normal constructor:\n";
	matrix2.print();

	// copy constructor 
	auto matrix3(matrix2);
	std::cout << "Copy constructor:\n";
	matrix3.print();

	// move constructor
	auto matrix4(std::move(matrix3));
	std::cout << "Move constructor:\n";
	matrix4.print();

    /// c) Implement the following for all rows in the matrix and for a given row in the matrix:
    /// Set/reset all bits; Flip the bits; Test if none, all or any bits are set; Access the elements; Count the number of set bits.
    // The implemented class is defined in "BitMatrix.hpp". We test the row operations below:

	BitMatrix<3, 4> matrix;
	matrix.set(); // Set all bits in all rows
	matrix.reset(); // Reset all bits in all rows
	matrix.flip(); // Flip all bits in all rows
	std::cout << "The matrix:\n";
	matrix.print();

	// test if none, all or any bits are set 
	std::cout << std::boolalpha;
	std::cout << "Checking if bits are set " << matrix2.all() << std::endl;
	std::cout << "Checking if no bits are set " << matrix2.none() << std::endl;
	std::cout << "Checking if any bits are set " << matrix2.any() << std::endl;

	// access the elements 
	BitMatrix<3, 4> mat(9);
	std::cout << "The matrix:\n";
	mat.print();
	
	std::size_t x = 2;
	std::size_t y = 2;
	std::cout << "Matrix[2]: " << mat[2] << std::endl; // access a row
	std::cout << "Matrix[2][1]: " << mat[2][1] << std::endl; // access an element

	// count the number of set bits
	std::cout << "Count number of set bits: " << mat.count() << std::endl;

    /// d) Create member functions for OR, XOR and AND Boolean operations on bit matrices.
    // The implemented class is defined in "BitMatrix.hpp". We test the bitwise operations below:

	BitMatrix<3, 4> mat1(9);
	BitMatrix<3, 4> mat2(8);
	std::cout << "Matrix1:\n";
	mat1.print();
	std::cout << "Matrix2:\n";
	mat2.print();

	// Perform OR operation on the matrices
	std::cout << "Matrix1 OR Matrix2\n";
	BitMatrix<3, 4> resultOR = mat1 | mat2;
	resultOR.print();
	BitMatrix<3, 4> resultOR2 = matrix1;
	resultOR2 |= mat1; 

	// Perform AND operation on the matrices
	std::cout << "Matrix1 AND Matrix2\n";
	BitMatrix<3, 4> resultAND = mat1 & mat2;
	resultAND.print();
	BitMatrix<3, 4> resultAND2 = matrix1;
	resultAND2 |= mat1;

	// Perform XOR operation on the matrices
	std::cout << "Matrix1 XOR Matrix2\n";
	BitMatrix<3, 4> resultXOR = mat1 ^ mat2;
	resultXOR.print();
	BitMatrix<3, 4> resultXOR2 = matrix1;
	resultXOR2 |= mat1;

}