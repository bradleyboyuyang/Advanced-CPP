/*
    Level 2.2: Smart Pointers in Boost and C++
    Problem 1: First Encounters with Smart Pointers: Unique Pointers

    Name: Boyu Yang
    Point.hpp: Class implementation for the Point Class

*/

#pragma once

#include <iostream>

// Point class implementation
class Point {
public:
    // default constructor
    Point()=default;
    // normal constructor
    Point(double d1, double d2) : x(d1), y(d2) {};
    // change x
    void X(double new_x) {
        x = new_x;
    }
    // change y
    void Y(double new_y) {
        y = new_y;
    }
    // destructor
    // we print a message to confirm when the Point class object is cleared
    ~Point() { std::cout << "Destructor of Point" << std::endl; };
private:
    double x; double y;
};
