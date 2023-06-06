/*
	Level 2.8: STL Bitset and Boost Dynamic Bitset
	Problem 5: std::vector<bool> versus Bitset
	BitMatrix.cpp: Class Implementation for BitMatrix
	Name: Boyu Yang
*/

#include "BitMatrix.hpp"

/// b) Constructors need to be created. Use the same defaults as with std::bitset<M>.
// default constructor
template<std::size_t N, std::size_t M>
BitMatrix<N, M>::BitMatrix() = default;

// constructor: set all row equal to the same value
template<std::size_t N, std::size_t M>
BitMatrix<N, M>::BitMatrix(bool value) {
	for (auto& row : matrix) {
		row = std::bitset<M>(value);
	}
}

// copy constructor
template<std::size_t N, std::size_t M>
BitMatrix<N, M>::BitMatrix(BitMatrix<N, M>& mat) {
	matrix = mat.matrix;
}

// move constructor
template<std::size_t N, std::size_t M>
BitMatrix<N, M>::BitMatrix(BitMatrix<N, M>&& mat) {
	matrix = std::move(mat.matrix);
}

/// c) Implement the following for all rows in the matrix and for a given row in the matrix:
//• Set/reset all bits.
//• Flip the bits.
//• Test if none, all or any bits are set.
//• Access the elements.
//• Count the number of set bits.

template<std::size_t N, std::size_t M>
void BitMatrix<N, M>::set() {
    for (auto& row : matrix_) {
        row.set();
    }
}

template<std::size_t N, std::size_t M>
void BitMatrix<N, M>::reset() {
    for (auto& row : matrix_) {
        row.reset();
    }
}

template<std::size_t N, std::size_t M>
void BitMatrix<N, M>::flip() {
    for (auto& row : matrix_) {
        row.flip();
    }
}

template<std::size_t N, std::size_t M>
bool BitMatrix<N, M>::none() const {
    for (const auto& row : matrix_) {
        if (row.any()) {
            return false;
        }
    }
    return true;
}

template<std::size_t N, std::size_t M>
bool BitMatrix<N, M>::all() const {
    for (const auto& row : matrix_) {
        if (!row.all()) {
            return false;
        }
    }
    return true;
}

template<std::size_t N, std::size_t M>
bool BitMatrix<N, M>::any() const {
    for (const auto& row : matrix_) {
        if (row.any()) {
            return true;
        }
    }
    return false;
}

template<std::size_t N, std::size_t M>
std::bitset<M>& BitMatrix<N, M>::operator[](std::size_t index) {
    return matrix_[index];
}

template<std::size_t N, std::size_t M>
const std::bitset<M>& BitMatrix<N, M>::operator[](std::size_t index) const {
    return matrix_[index];
}

template<std::size_t N, std::size_t M>
std::size_t BitMatrix<N, M>::count() const {
    std::size_t totalCount = 0;
    for (const auto& row : matrix_) {
        totalCount += row.count();
    }
    return totalCount;
}

