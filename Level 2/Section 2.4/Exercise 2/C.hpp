/*
    Level 2.2: Smart Pointers in Boost and C++
    Problem 2: Shared Pointers

    Name: Boyu Yang
    C.hpp: Class implementations for the required C1 and C2 classes

*/

#pragma once

#include <iostream>
#include <memory>

/// a) Create the code for the classes C1 and C2 each of which contains the shared object from the value d above
class C1
{
private:
    //double* d; OLD WAY 
    std::shared_ptr<double> d;
public:
    C1(std::shared_ptr<double> value) : d(value) {}
    virtual ~C1() { std::cout << "\nC1 destructor\n"; }
    void print() const { std::cout << "Value " << *d; }
};

// In both classes, the shared object d is of type std::shared_ptr<double>
class C2
{
private:
    //double* d; OLD WAY 
    std::shared_ptr<double> d;
public:
    C2(std::shared_ptr<double> value) : d(value) {}
    virtual ~C2() { std::cout << "\nC2 destructor\n"; }
    void print() const { std::cout << "Value " << *d; }
};



class C3
{
private:
    //double* d; OLD WAY 
    std::shared_ptr<Point> ptr;
public:
    C3(std::shared_ptr<Point> value) : ptr(value) {}
    virtual ~C3() { std::cout << "\nC3 destructor\n"; }
    void print() const { std::cout << "Value x: " << ptr->x << "Value y: " << ptr->y; }
};