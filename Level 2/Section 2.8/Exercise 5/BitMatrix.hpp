/*
	Level 2.8: STL Bitset and Boost Dynamic Bitset
	Problem 5: std::vector<bool> versus Bitset
	BitMatrix.hpp: Prototypes for BitMatrix class
	Name: Boyu Yang
*/
#pragma once

#include <iostream>
#include <bitset>
#include <vector>
#include <array>
#include <boost/dynamic_bitset.hpp>

template<std::size_t N, std::size_t M>
class BitMatrix {
public:
	/// b) Constructors need to be created. Use the same defaults as with std::bitset<M>.
	BitMatrix(); // default constructor
	BitMatrix(bool);
	BitMatrix(BitMatrix<N, M>&); // copy constructor
	BitMatrix(BitMatrix<N, M>&&); // move constructor

	/// c) Implement the following for all rows in the matrix and for a given row in the matrix:
	//• Set/reset all bits.
	//• Flip the bits.
	//• Test if none, all or any bits are set.
	//• Access the elements.
	//• Count the number of set bits.
	void set();
	void reset();
	void print();
	void flip();
	void flip(int);
	bool none();
	bool none(int);
	bool any();
	bool any(int);


private:
	std::array<std::bitset<M>, N> matrix;
};







/// d) Create member functions for OR, XOR and AND Boolean operations on bit matrices.