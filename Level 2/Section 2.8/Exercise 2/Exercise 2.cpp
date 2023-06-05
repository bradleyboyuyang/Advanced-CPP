/*
    Level 2.8: STL Bitset and Boost Dynamic Bitset
    Problem 2: Boolean Operations on Bitsets

    Name: Boyu Yang

    Problem objective:
    a) Create two bitsets bs1 and bs2 (they must have the same number of bits, that is the same size).
    b) Toggle all the bits of bs1 and bs2;
    c) Perform bitwise XOR, OR and AND on bs1 and bs2.
    d) Perform right and left shift operations on bs1 and bs2.
    e) Use std::hash to create hashed values for bs1 and bs2.
    f) Investigate how to create binary literals in C++ (since C++14) and their relationship with bitsets
    g) Create a byte in different ways: from a binary literal, from an integer, as binary logical operators on
    existing bytes.
    h) Perform bitwise operations on bytes (AND, OR).
    i) Perform left and right shift operations on bytes. Consider “extreme cases” of shifting.
    j) Can you think of examples/applications where bytes and bitsets can be used, for example raw
    memory access and savings and performance improvements?
*/

#include <iostream>
#include <iomanip>
#include <bitset>
#include <functional>
#include <boost/dynamic_bitset.hpp>

int main() {
    /// a) Create two bitsets bs1 and bs2 (they must have the same number of bits, that is the same size).
    const int N = 8;
    std::bitset<N> bs1(std::string("1010"));
    std::bitset<N> bs2(std::string("0101"));

    /// b) Toggle all the bits of bs1 and bs2;
    bs1.flip();
    std::cout << "bitset1: " << bs1 << std::endl;
    bs2.flip();
    std::cout << "bitset2: " << bs2 << std::endl;

    /// c) Perform bitwise XOR, OR and AND on bs1 and bs2.
    std::cout << "bitwise XOR: " << (bs1 ^ bs2) << std::endl;
    std::cout << "bitwise OR: " << (bs1 | bs2) << std::endl;
    std::cout << "bitwise AND: " << (bs1 & bs2) << std::endl;

    /// d) Perform right and left shift operations on bs1 and bs2.
    std::cout << "right shift bitset1 by 2 positions: " << (bs1>>2) << std::endl;
    std::cout << "left shift bitset2 by 3 positions: " << (bs2<<3) << std::endl;

    /// e) Use std::hash to create hashed values for bs1 and bs2.
    std::hash<std::bitset<N>> hasher; // create a hasher
    std::size_t hashValue1 = hasher(bs1);
    std::cout << "Hash values of bitset1: " << hashValue1 << std::endl;
    std::size_t hashValue2 = hasher(bs2);
    std::cout << "Hash values of bitset2: " << hashValue2 << std::endl;

    /// f) Investigate how to create binary literals in C++ (since C++14) and their relationship with bitsets
    // given code
    auto blit = 0b0011;
    std::byte b{ 0b0011 }; // Create from a binary literal
    std::bitset<4> bs(blit);
    boost::dynamic_bitset<unsigned int> dbs(4); // all 0 by default
    dbs[1] = dbs[0] = 1;
    std::cout << "byte: " << std::to_integer<int>(b) << '\n';
    std::cout << "bitset: " << bs << '\n';
    std::cout << "dynamic bitset: " << dbs << '\n';

    /// g) Create a byte in different ways: from a binary literal, from an integer, as binary logical operators on existing bytes.
    // Create a byte from a binary literal
    std::byte byte1{ 0b0011 };

    // Create a byte from an integer value
    std::byte byte2{12};

    // Create a byte using binary logical operators on existing bytes
    std::byte byte3 = byte1 | byte2;

    std::cout << "byte1: " << std::to_integer<int>(byte1) << '\n';
    std::cout << "byte2: " << std::to_integer<int>(byte2) << '\n';
    std::cout << "byte3: " << std::to_integer<int>(byte3) << '\n';


    /// h) Perform bitwise operations on bytes (AND, OR).

    std::byte resultAND = byte1 & byte2;
    std::byte resultOR = byte1 | byte2;

    std::cout << "byte1 & byte2: " << std::to_integer<int>(resultAND) << '\n';
    std::cout << "byte1 | byte2: " << std::to_integer<int>(resultOR) << '\n';

    /// i) Perform left and right shift operations on bytes. Consider “extreme cases” of shifting.
    std::byte resultLeftShift = byte3 << 2;  // Left shift by 2 position
    std::byte resultRightShift = byte3 >> 4;  // Right shift by 4 position, turn into zero

    std::cout << "Left shift byte3 by 2 position: " << std::to_integer<int>(resultLeftShift) << '\n';
    std::cout << "Right shift byte3 by 4 position: " << std::to_integer<int>(resultRightShift) << '\n';

    /// j) Can you think of examples/applications where bytes and bitsets can be used, for example raw
    /// memory access and savings and performance improvements?    
    // Bytes and bitsets can be used in memory allocation, Huffman coding, flags and configurations, 
    // represent sparse matrices, genetic algorithms, security and access control, etc.

}