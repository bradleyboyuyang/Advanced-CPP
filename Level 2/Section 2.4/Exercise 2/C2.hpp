/*
    Level 2.2: Smart Pointers in Boost and C++
    Problem 2: Shared Pointers

    Name: Boyu Yang
    C2.hpp: Class implementations for the modified C1 and C2 classes in Question (c)

*/

#pragma once

#include <iostream>
#include <memory>
#include "Point.hpp"

/// c) Carry out the same exercise as in steps a) and b) but with a user-defined type as shared data: std::shared_ptr<Point> p;
class NewC1
{
private:
    std::shared_ptr<Point> p;

public:
    NewC1(std::shared_ptr<Point> value) : p(value) {}
    virtual ~NewC1() { std::cout << "\nNewC1 destructor\n"; }
    void print() const { p->print(); }
};
// The two classes now share the object pointer ``std::shared_ptr<Point> p``;
class NewC2
{
private:
    std::shared_ptr<Point> p;

public:
    NewC2(std::shared_ptr<Point> value) : p(value) {}
    virtual ~NewC2() { std::cout << "\nNewC2 destructor\n"; }
    void print() const { p->print(); }
};