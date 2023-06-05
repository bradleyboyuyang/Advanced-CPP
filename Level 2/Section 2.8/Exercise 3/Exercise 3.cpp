/*
    Level 2.8: STL Bitset and Boost Dynamic Bitset
    Problem 3: Boost Dynamic Bitset 101

    Name: Boyu Yang

    Problem objective:
    a) Port the code that you created in questions 1 and 2 to boost::dynamic_bitset<T>. Test your code.
    b) (Changing the size of a bitset at run-time). Apply resize(), clear(), push_back(), pop_back()
    and append() to bitset instances.
    c) (Set operations). Test the functionality to test if a bitset is a subset (or proper subset) of another bitset.
    d) (Searching in bitsets). Use find_first() and find_next() to search for bits in bitsets.
*/

#include <iostream>
#include <iomanip>
#include <bitset>
#include <functional>
#include <boost/dynamic_bitset.hpp>

int main() {
    /// a) Port the code that you created in questions 1 and 2 to boost::dynamic_bitset<T>. Test your code.
    // =========================== 
    // Exercise 1 Code using Boost
    // =========================== 
    std::cout << "================================" << std::endl;
    std::cout << "Code from Exercise 1 using Boost" << std::endl;
    std::cout << "================================" << std::endl;
    /// a) Create bitsets from unsigned long and unsigned long long.
    const int M = 7;
    unsigned long val1 = 12;
    unsigned long long val2 = 123;
    boost::dynamic_bitset<> bs_1(M, val1);
    std::cout << bs_1 << std::endl;
    boost::dynamic_bitset<> bs_2(M, val2);
    std::cout << bs_2 << std::endl;

    /// b) Create bitsets from full strings (for example, “01010”). Create a bitset from parts of strings based on a
    /// start index and the number of bits to use.
    boost::dynamic_bitset<> bs3(std::string("1101")); // result: 0001101
    std::cout << bs3 << std::endl;
    int index = 1;
    int num_bits = 4;
    // start from index 1, use 4 bits, result: 0001010
    boost::dynamic_bitset<> bs4(std::string("1101011"), index, num_bits);
    std::cout << bs4 << std::endl;

    /// c) In the case of strings (for example), use exception handling to check for out-of-range values and invalid
    /// arguments (bits that are neither 0 nor 1).
    std::string str = "010101";
    try {
        boost::dynamic_bitset<> bs(std::string("010101", 8, 12)); // out of range
        //boost::dynamic_bitset<> _bs(std::string("123456", 3)); // invalid arguments
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument! " << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Out of range! " << std::endl;
    }

    /// d) Set the bits in a bitset in different ways :
    // • Set / reset all bits.
    // • Flip the bits.
    // • Test if none, all or any bits are set.
    // • Access the elements.
    // • Count the number of set bits.
    boost::dynamic_bitset<> bits(M, 123);
    std::cout << bits << std::endl;
    // set, reset, flip
    bits.set();       // Set all bits to 1
    std::cout << bits << std::endl;
    bits.reset();     // Reset all bits to 0
    std::cout << bits << std::endl;
    bits.flip();      // Flip all bits (1s become 0s and vice versa)
    std::cout << bits << std::endl;
    // test if none, all, or any bits are set
    std::cout << "If all bits are set: " << std::boolalpha << bits.all() << std::endl;
    std::cout << "If no bits are set: " << std::boolalpha << bits.none() << std::endl;
    std::cout << "If any bits are set: " << std::boolalpha << bits.any() << std::endl;
    // access the elements
    std::cout << "Element at index 2: " << std::boolalpha << bits[2] << std::endl;
    // count the number of set bits
    std::cout << "Number of set bits: " << std::boolalpha << bits.count() << std::endl;

    /// e) Convert a bitset to std::string, unsigned long and unsigned long long.
    // type conversions
    boost::dynamic_bitset<> bitset7(M, 123);
    std::cout << bitset7 << std::endl;
    // boost bitset does not support converting to string or ullong 
    //std::string bitsetToString = bitset7.to_string(); // Convert bitset to std::string
    //std::cout << bitsetToString << std::endl;
    unsigned long bitsetToULong = bitset7.to_ulong(); // Convert bitset to unsigned long
    std::cout << bitsetToULong << std::endl;
    //unsigned long long bitsetToULLong = bitset7.to_ullong(); // Convert bitset to unsigned long long
    //std::cout << bitsetToULLong << std::endl;

    /// Part (F) Test if two bitsets are equal or unequal.
    std::bitset<8> bitset8("10101010");
    std::bitset<8> bitset9("11001100");
    std::cout << "If two bitsets are equal: " << std::boolalpha << (bitset8 == bitset9) << std::endl;
    std::cout << "If two bitsets are not equal: " << std::boolalpha << (bitset8 != bitset9) << std::endl;

    // =========================== 
    // Exercise 2 Code using Boost
    // =========================== 
    std::cout << "================================" << std::endl;
    std::cout << "Code from Exercise 2 using Boost" << std::endl;
    std::cout << "================================" << std::endl;
    /// a) Create two bitsets bs1 and bs2 (they must have the same number of bits, that is the same size).
    const int N = 8;
    boost::dynamic_bitset<> bs1(std::string("1010"));
    boost::dynamic_bitset<> bs2(std::string("0101"));

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
    std::cout << "right shift bitset1 by 2 positions: " << (bs1 >> 2) << std::endl;
    std::cout << "left shift bitset2 by 3 positions: " << (bs2 << 3) << std::endl;

    /// e) Use std::hash to create hashed values for bs1 and bs2.
    std::hash<boost::dynamic_bitset<>> hasher; // create a hasher
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
    std::byte byte2{ 12 };
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

    // =========================== 
    // Exercise 3 Code
    // =========================== 
    std::cout << "===================" << std::endl;
    std::cout << "Code for Exercise 3" << std::endl;
    std::cout << "===================" << std::endl;

    /// b) (Changing the size of a bitset at run-time). Apply resize(), clear(), push_back(), pop_back()
    /// and append() to bitset instances.
    boost::dynamic_bitset<> bittest(std::string("1101010"));
    std::cout << "Original bitset: " << bittest << std::endl;
    bittest.resize(6); // resize the bitset, adding zero or chopping the higher term
    std::cout << "Bitset after resize: " << bittest << std::endl;
    bittest.push_back(true); // push at the left-most digit
    std::cout << "bitset after push_back: " << bittest << std::endl;
    bittest.pop_back(); // pop from the left-most digit
    std::cout << "bitset after pop_back: " << bittest << std::endl;
    bittest.append(1); // 
    std::cout << "bitset after append: " << bittest << std::endl;
    bittest.clear(); // clear bitset
    std::cout << "bitset after clear: " << bittest << std::endl;

    /// c) (Set operations). Test the functionality to test if a bitset is a subset (or proper subset) of another bitset.
    boost::dynamic_bitset<> bitset1(std::string("101010"));
    boost::dynamic_bitset<> bitset2(std::string("110110"));
    boost::dynamic_bitset<> bitset3(std::string("101010"));
    boost::dynamic_bitset<> bitset4(std::string("001010"));
    std::cout << "b1: " << bitset1 << std::endl;
    std::cout << "b2: " << bitset2 << std::endl;
    std::cout << "b3: " << bitset3 << std::endl;
    std::cout << "b2 is bitset of b3? " << bitset2.is_subset_of(bitset3) << std::endl;
    std::cout << "b4 is bitset of b3? " << bitset4.is_subset_of(bitset3) << std::endl;

    /// d) (Searching in bitsets). Use find_first() and find_next() to search for bits in bitsets.
    boost::dynamic_bitset<> bitset(10); // Create a dynamic bitset of size 10
    // Set some bits in the bitset
    bitset[2] = 1; bitset[5] = 1; bitset[8] = 1;
    std::cout << "bitset: " << bitset << std::endl; // now bitset becomes 0100100100
    std::cout << "First bit: " << bitset.find_first() << std::endl; //first set bit from position 0, therefore 2
    std::cout << "Next bit: " << bitset.find_next(2) << std::endl; //next set bit from position 2, therefore 5
        
}