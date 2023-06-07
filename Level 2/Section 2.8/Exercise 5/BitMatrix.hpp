/*
	Level 2.8: STL Bitset and Boost Dynamic Bitset
	Problem 5: std::vector<bool> versus Bitset
	BitMatrix.hpp: Class Implementation for BitMatrix
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
	// default constructor
	BitMatrix() = default;
	// constructor: set all row equal to the same value
	BitMatrix(unsigned long val) {
		for (auto& row : matrix) {
			row = std::bitset<M>(val);
		}
	}
	// copy constructor
	BitMatrix(BitMatrix<N, M>& mat) {
		matrix = mat.matrix;
	}
	// move constructor
	BitMatrix(BitMatrix<N, M>&& mat) {
		matrix = std::move(mat.matrix);
	}

	/// c) Implement the following for all rows in the matrix and for a given row in the matrix:
	//• Set/reset all bits.
	//• Flip the bits.
	//• Test if none, all or any bits are set.
	//• Access the elements.
	//• Count the number of set bits.
	
	// set all bits
	void set() {
		for (auto& row : matrix) {
			row.set();
		}
	}

	// reset all bits
	void reset() {
		for (auto& row : matrix) {
			row.reset();
		}
	}

	// print a matrix
	void print() {
		for (int i = 0; i < matrix.size(); ++i) {
			std::cout << matrix[i] << "\n";
		};
	}

	// flip all bits
	void flip() {
		for (auto& row : matrix) {
			row.flip();
		}
	}

	// test if none of bits are set
	bool none() const {
		for (const auto& row : matrix) {
			if (row.any()) {
				return false;
			}
		}
		return true;
	}

	// test if all bits are set
	bool all() const {
		for (const auto& row : matrix) {
			if (!row.all()) {
				return false;
			}
		}
		return true;
	}

	// test if any bits is set
	bool any() const {
		for (const auto& row : matrix) {
			if (row.any()) {
				return true;
			}
		}
		return false;
	}

	// access a row
	std::bitset<M>& operator[] (std::size_t index) {
		return matrix[index];
	}

	// count the number of set bits
	std::size_t count() const {
		std::size_t totalCount = 0;
		for (const auto& row : matrix) {
			totalCount += row.count();
		}
		return totalCount;
	}

	/// d) Create member functions for OR, XOR and AND Boolean operations on bit matrices.
	// define OR
	BitMatrix<N, M>& operator |= (const BitMatrix<N, M>& other) {
		for (std::size_t i = 0; i < N; ++i) {
			matrix[i] |= other.matrix[i];
		}
		return *this;
	}

	BitMatrix<N, M>& operator | (const BitMatrix<N, M>& other) {
		BitMatrix<N, M> output;
		for (std::size_t i = 0; i < N; ++i) {
			output[i] = (matrix[i] | other.matrix[i]);
		}
		return output;
	}


	// define XOR
	BitMatrix<N, M>& operator ^= (const BitMatrix<N, M>& other) {
		for (std::size_t i = 0; i < N; ++i) {
			matrix[i] ^= other.matrix[i];
		}
		return *this;
	}

	BitMatrix<N, M>& operator ^ (const BitMatrix<N, M>& other) {
		BitMatrix<N, M> output;
		for (std::size_t i = 0; i < N; ++i) {
			output[i] = (matrix[i] ^ other.matrix[i]);
		}
		return output;
	}

	// define AND
	BitMatrix<N, M>& operator&=(const BitMatrix<N, M>& other) {
		for (std::size_t i = 0; i < N; ++i) {
			matrix[i] &= other.matrix[i];
		}
		return *this;
	}

	BitMatrix<N, M>& operator & (const BitMatrix<N, M>& other) {
		BitMatrix<N, M> output;
		for (std::size_t i = 0; i < N; ++i) {
			output[i] = (matrix[i] & other.matrix[i]);
		}
		return output;
	}

private:
	std::array<std::bitset<M>, N> matrix;
};



