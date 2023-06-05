/*
    Level 2.8: STL Bitset and Boost Dynamic Bitset
    Problem 4: std::vector<bool> versus Bitset

    Name: Boyu Yang

    Problem objective:
    a) Determine which functionality it supports compared to the two bitset classes discussed here.
    b) Create a function to compute the intersection of two instances std::vector<bool>.
    Having completed the exercise will probably convince you that it is better to use bitset classes instead of
    std::vector<bool>?
*/

#include <iostream>
#include <bitset>
#include <vector>
#include <boost/dynamic_bitset.hpp>

/// b) Create a function to compute the intersection of two instances std::vector<bool>.
std::vector<bool> computeIntersection(const std::vector<bool>& vector1, const std::vector<bool>& vector2) {
    std::vector<bool> result;
    // Ensure that both vectors have the same size
    if (vector1.size() != vector2.size()) {
        return result;
    }
    // Compute the intersection by performing element-wise AND
    for (std::size_t i = 0; i < vector1.size(); ++i) {
        result.push_back(vector1[i] && vector2[i]);
    }
    return result;
}

int main() {
    /// a) Determine which functionality it supports compared to the two bitset classes discussed here.
    // std::vector<bool> suppports pop_back(), push_back(), clear(), empty(), size(), at(), resize(), etc.
    // However, bool vector does not support bit manipulation operations (bitwise AND, OR, XOR, NOT), 
    // count() to get the number of bits, and to_string() to do type conversion.

    /// b) Create a function to compute the intersection of two instances std::vector<bool>.
    std::vector<bool> vector1 = { true, false, true, false };
    std::vector<bool> vector2 = { false, true, true, false };
    // compute intersection
    std::vector<bool> intersection = computeIntersection(vector1, vector2);
    // Print the intersection
    for (bool bit : intersection) {
        std::cout << bit << " ";
    }
    std::cout << std::endl;

    /// Having completed the exercise will probably convince you that it is better to use bitset classes instead of std::vector<bool> ?
    // Yes, the main power of bitset is bitwise manipulations, which bool vectors are hard to use

}