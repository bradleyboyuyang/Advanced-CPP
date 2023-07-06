/*
    Level 3.1: STL Algorithms I
    Problem 1: Adapter Classes for Bitsets

    Name: Boyu Yang
    File: Proposition.hpp
    Description: class interface

*/

#pragma once

#include <iostream>
#include <bitset>


class Proposition
{ // A class representing true/false
private:
    std::bitset<1> data;
public:
    /// a) Create the following constructors: default, bool as argument and a std::bitset<1> as argument
    Proposition(); // default constructor
    Proposition(bool arg); // bool as argument
    Proposition(std::bitset<1> arg); // bitset as arg

    /// b) Implement the above Boolean operators as members with the exception of conditional and 
    /// biconditional which should be non - member friends
    bool operator==(const Proposition&);		// equality
    bool operator!=(const Proposition&);		// inequality
    Proposition operator&(const Proposition&);	// and
    Proposition operator|(const Proposition&);	// or
    Proposition operator^(const Proposition&);	// xor
    Proposition operator!();				    // negation
    void operator=(bool);          // assign
    // Friend functions for conditional (->) and biconditional (<->)
    friend Proposition operator%(const Proposition&, const Proposition&);
    friend Proposition operator%=(const Proposition&, const Proposition&);
    // friend function to print the values
    friend std::ostream& operator<<(std::ostream&, const Proposition&);
};