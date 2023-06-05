/*
    Level 2.8: STL Bitset and Boost Dynamic Bitset
    Problem 1: STL Bitset 101

    Name: Boyu Yang

    Problem objective:
    a) Create bitsets from unsigned long and unsigned long long.
    b) Create bitsets from full strings (for example, “01010”). Create a bitset from parts of strings based on a
    start index and the number of bits to use.
    c) In the case of strings (for example), use exception handling to check for out-of-range values and invalid
    arguments (bits that are neither 0 nor 1).
    d) Set the bits in a bitset in different ways:
    • Set/reset all bits.
    • Flip the bits.
    • Test if none, all or any bits are set.
    • Access the elements.
    • Count the number of set bits.
    e) Convert a bitset to std::string, unsigned long and unsigned long long.
    f) Test if two bitsets are equal or unequal.
*/

#include <iostream>
#include <bitset>


int main() {

    /// Part (A) Create bitsets from unsigned long and unsigned long long.
    const int N = 7;
    unsigned long val1 = 12;
    unsigned long long val2 = 123;
    std::bitset<N> bs1(val1);
    std::cout << bs1 << std::endl;
    std::bitset<N> bs2(val2);
    std::cout << bs2 << std::endl;
        
    /// Part (B) Create bitsets from full strings (for example, “01010”). Create a bitset from parts of strings based on a
    /// start index and the number of bits to use.
    std::bitset<N> bs3(std::string("1101")); // result: 0001101
    std::cout << bs3 << std::endl;

    int index = 1;
    int num_bits = 4;
    // start from index 1, use 4 bits, result: 0001010
    std::bitset<N> bs4(std::string("1101011"), index, num_bits); 
    std::cout << bs4 << std::endl;

    /// Part (C) In the case of strings (for example), use exception handling to check for out-of-range values and invalid
    /// arguments (bits that are neither 0 nor 1).
    std::string str = "010101";
    try {
        std::bitset<N> bs(std::string("010101", 8, 12)); // out of range
        //std::bitset<N> _bs(std::string("123456", 3)); // invalid arguments
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument! " << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Out of range! " << std::endl;
    }

    /// Part (D) Set the bits in a bitset in different ways :
    // • Set / reset all bits.
    // • Flip the bits.
    // • Test if none, all or any bits are set.
    // • Access the elements.
    // • Count the number of set bits.

    std::bitset<N> bits;
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

    /// Part (E) Convert a bitset to std::string, unsigned long and unsigned long long.
    // type conversions
    std::bitset<N> bitset7(123);
    std::cout << bitset7 << std::endl;
    std::string bitsetToString = bitset7.to_string(); // Convert bitset to std::string
    std::cout << bitsetToString << std::endl;
    unsigned long bitsetToULong = bitset7.to_ulong(); // Convert bitset to unsigned long
    std::cout << bitsetToULong << std::endl;
    unsigned long long bitsetToULLong = bitset7.to_ullong(); // Convert bitset to unsigned long long
    std::cout << bitsetToULLong << std::endl;

    /// Part (F) Test if two bitsets are equal or unequal.
    std::bitset<8> bitset8("10101010");
    std::bitset<8> bitset9("11001100");
    std::cout << "If two bitsets are equal: " << std::boolalpha << (bitset8 == bitset9) << std::endl;
    std::cout << "If two bitsets are not equal: " << std::boolalpha << (bitset8 != bitset9) << std::endl;

}