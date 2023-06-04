/*
    Level 2.1: Type Traits
    Problem 4: Supported Operations

    Name: Boyu Yang

    Problem objective:
    For the given class, answer the following questions:
    a) Programmatically determine if type Point has a virtual destructor.
    b) Programmatically determine if type Point has the following constructors: default, copy, move.
    c) Programmatically determine if type Point is copy assignable/move assignable.
    d) Set the copy constructor and assignment operator as ‘deleted functions’ and perform steps b)-c) again;
    do you get the same result?
    e) Add move semantics code (explicit move constructor and move assignment operator) and perform
    steps b)-c) again; do you get the same result?

*/

#include <iostream>
#include <type_traits>

class Shape {
public:
    virtual void draw() = 0;
};

class Point : public Shape
{
public:
    // default constructor
    Point() {};

    /// Part (D), set copy constructor and assignment operator as "deleted"
    // copy constructor
    //Point(Point& p) = delete;
    
    // assignment operator
    //Point& operator = (const Point& p) = delete;

    /// Part (E), add explicit move constructor and move assignment operator
    // explicit move constructor
    //Point(Point&& p) {};
    
    // move assignment operator
    //Point& operator = (const Point&& p) {};

    virtual void draw() override {}
};


int main()
{
    Shape* shape;
    Point* point;
    /// Part (A) Programmatically determine if type Point has a virtual destructor.
    std::cout << "Has Virtual Destructor? " << std::boolalpha << std::has_virtual_destructor<Point>::value << std::endl; // false

    /// Part (B) Programmatically determine if type Point has the following constructors : default, copy, move.
    std::cout << "Default constructible? " << std::boolalpha << std::is_default_constructible<Point>::value << std::endl; // true
    std::cout << "Copy constructible? " << std::boolalpha << std::is_copy_constructible<Point>::value << std::endl; // true
    std::cout << "Move constructible? " << std::boolalpha << std::is_move_constructible<Point>::value << std::endl; // true

    /// Part (C) Programmatically determine if type Point is copy assignable / move assignable.
    std::cout << "Copy assignable? " << std::boolalpha << std::is_copy_assignable<Point>::value << std::endl; // true
    std::cout << "Move assignable? " << std::boolalpha << std::is_move_assignable<Point>::value << std::endl; // true

    /// Part (D) Set the copy constructor and assignment operator as ‘deleted functions’ and perform steps b) - c) again;
    /// do you get the same result?
    // Uncomment the code in the class under "Part (D)" we can get:
    // The type Point is default constructible, but not copy constructible, move constructible, copy assignable, nor move assignable.

    /// Part (E) Add move semantics code(explicit move constructor and move assignment operator) and perform
    /// steps b) - c) again; do you get the same result ?
    // Uncomment the code in the class under "Part (E)" we can get:
    // The type Point is default constructible, move constructible, move assignable, but not copy constructible and copy assignable.

}


