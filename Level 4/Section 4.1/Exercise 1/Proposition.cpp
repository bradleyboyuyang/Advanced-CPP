/*
    Level 3.1: STL Algorithms I
    Problem 1: Adapter Classes for Bitsets

    Name: Boyu Yang
    File: Proposition.hpp
    Description: class implementation

*/

#include "Proposition.hpp"

/// a) Create the following constructors: default, bool as argument and a std::bitset<1> as argument
Proposition::Proposition() : data(0) {};
Proposition::Proposition(bool arg) { data.set(0, arg); };
Proposition::Proposition(std::bitset<1> arg) : data(arg) {};

/// b) Implement the above Boolean operators as members with the exception of conditional and 
/// biconditional which should be non - member friends
bool Proposition::operator==(const Proposition& p) { return p.data == this->data; };		 // equality
bool Proposition::operator!=(const Proposition& p) { return p.data != this->data; };		 // inequality
Proposition Proposition::operator&(const Proposition& p) { return Proposition(p.data & this->data); }; // and
Proposition Proposition::operator|(const Proposition& p) { return Proposition(p.data | this->data); }; // or
Proposition Proposition::operator^(const Proposition& p) { return Proposition(p.data ^ this->data); };	 // xor
Proposition Proposition::operator!() { return Proposition(~this->data); };								 // negation
void Proposition::operator=(bool val) { this->data.set(0, val); }; // assign a proposition to a bool

// friend function: Conditional operator (->)
Proposition operator%(const Proposition& left, const Proposition& right)
{
    return Proposition(~left.data | right.data);
}

// friend function: Biconditional operator (<->)
Proposition operator%=(const Proposition& left, const Proposition& right)
{
    return Proposition((~left.data | right.data) & (~right.data | left.data));
}

// friend function to print the values
std::ostream& operator<<(std::ostream& out, const Proposition& p) {
    out << std::boolalpha << p.data;
    return out;
};