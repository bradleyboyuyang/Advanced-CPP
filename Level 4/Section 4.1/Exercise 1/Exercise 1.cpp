/*
    Level 3.1: STL Algorithms I
    Problem 1: Adapter Classes for Bitsets

    Name: Boyu Yang

    Problem objective:
    In this exercise we create a class that models propositions in Boolean algebra (for this exercise you may
    need to review this topic). To this end, we create a class called Proposition that models propositions
    and the associated Boolean operators such as (A, B and C are propositions):
      Equality, inequality (A == B, A != B)
      Conjunction (AND) (A & B)
      Disjunction (OR) (A | B)
      Exclusive OR (XOR) (A ^B)
      Conditional (->) (A % B – operator% is overloaded, as modulo is inappropriate in this context)
      Biconditional (<->) (aka (A->B)&(B->A))
      Negation (!A)
      Assign a proposition to a bool
    a) Create the following constructors: default, bool as argument and a std::bitset<1> as argument.
    b) Implement the above Boolean operators as members with the exception of conditional and
    biconditional which should be non-member friends. Test each operator separately.
    c) Check that your code satisfies De Morgan’s Laws:
      NOT (A OR B) == NOT(A) AND NOT(B)
      NOT (A AND B) == NOT(A) OR NOT(B).
    d) Check that your code satisfies the Distributive Laws:
      A AND(B OR C) == (A AND B) OR (A OR C)
      A OR(B AND C) == (A OR B) AND (A OR C).
    e) Let A, B and C be propositions. Check that the statement form:
      [A -> (B -> C)] <-> [(A & B) -> C]
    Is a tautology (that is, it always returns true for all assignments of truth values to its statement letters A,B
    and C). There are eight options to be checked.
    In all code delegate to std::bitset<1> and use as much of the underlying mathematics as possible.
*/

#include <iostream>
#include <array>
#include "Proposition.hpp"

int main() {
    Proposition A(true);
    Proposition B(false);
    Proposition C(true);

    /// c) check the De Morgan's Laws
    std::cout << std::boolalpha;
    std::cout << "NOT (A OR B) == NOT(A) AND NOT(B): " << (!(A | B) == (!A & !B)) << std::endl;
    std::cout << "NOT (A AND B) == NOT(A) OR NOT(B): " << (!(A & B) == (!A | !B)) << std::endl;

    /// d) Check that your code satisfies the Distributive Laws
    std::cout << "A AND(B OR C) == (A AND B) OR (A OR C): " << (A & (B | C) == ((A & B) | (A & C))) << std::endl;
    std::cout << "A OR(B AND C) == (A OR B) AND (A OR C): " << (A | (B & C) == ((A | B) & (A | C))) << std::endl;

    /// e) check tautology
    std::array<Proposition, 2> arr{ Proposition(true), Proposition(false) };
    for (auto A : arr) {
        for (auto B : arr) {
            for (auto C : arr) {
                std::cout << "Values: " << A << B << C << " LHS and RHS equal? " << ((A % (B % C)) == ((A & B) % C)) << std::endl;
            };
        };
    };
    // we can see for all possible cases the statement is true. Therefore it is a tautology.
}

