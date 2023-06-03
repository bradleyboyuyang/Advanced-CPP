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
    Point() {}
    virtual void draw() override {}
};

template <typename T>
void MethodInformation(const T& t)
{
    // Numeric type 
    std::cout << "Default constructible? " << std::boolalpha << std::is_default_constructible<T>::value << std::endl;
    std::cout << "Copy constructible? " << std::boolalpha << std::is_copy_constructible<T>::value << std::endl;
    std::cout << "Move constructible? " << std::boolalpha << std::is_move_constructible<T>::value << std::endl;
    std::cout << "Copy assignable? " << std::boolalpha << std::is_copy_assignable<T>::value << std::endl;
    std::cout << "Move assignable? " << std::boolalpha << std::is_move_assignable<T>::value << std::endl;
}

int main()
{
    Shape* shape;
    Point* point;
    /// Part (A) Programmatically determine if type Point has a virtual destructor.
    std::cout << "*** Has Virtual Destructor? : **** \n";
    std::cout << "Point: " << std::boolalpha << std::has_virtual_destructor<Point>::value << std::endl;
    
    /// Part (B) Programmatically determine if type Point has the following constructors : default, copy, move.
    /// Part (C) Programmatically determine if type Point is copy assignable / move assignable.
    // We answer the two questions using the defined 


    /// Part (D) Set the copy constructorand assignment operator as ‘deleted functions’and perform steps b) - c) again;
    /// do you get the same result ?


    /// Part (E) Add move semantics code(explicit move constructor and move assignment operator) and perform
    /// steps b) - c) again; do you get the same result ?
     


    // b) Programmatically determine if type Point has default constructor, move, copy .
    std::cout << "\n*** Default constructor? : **** \n";
    std::cout << "Point: " << std::boolalpha << std::is_default_constructible<Point>::value << std::endl;
    // result is True

    std::cout << "\n*** Default move? : **** \n";
    std::cout << "Point: " << std::boolalpha << std::is_move_constructible<Point>::value << std::endl;
    // result is True 

    std::cout << "\n*** Default copy? : **** \n";
    std::cout << "Point: " << std::boolalpha << std::is_copy_constructible<Point>::value << std::endl;
    // result is True

    // c) Programmatically determine if type Point is copy assignable/move assignable.
    std::cout << "\n*** Copy assignable? : **** \n";
    std::cout << "Point: " << std::boolalpha << std::is_copy_assignable<Point>::value << std::endl;
    // result is True

    std::cout << "\n*** move assignable? : **** \n";
    std::cout << "Point: " << std::boolalpha << std::is_move_assignable<Point>::value << std::endl;
    // result is True

    // d) Set the copy constructor and assignment operator as �deleted functions� and perform steps b)-c) again; do you get the same result?
    // Just re-ran program above and the following results were found:

    //      default destructor --> False (this is the same)
    //      default constructor --> False (this is different from the original)
    //      default move --> False (this is different from the original)
    //      default copy --> False (this is different from the original)
    //      copy assignable --> False (this is different from the original)
    //      move assignable --> False (this is different from the original)

    // e) Add move semantics code(explicit move constructor and move assignment operator)
    //    and perform steps b) - c) again; do you get the same result ?

    //      virtual destructor -->  False (this is the same as the original)
    //      default constructor --> True (this is the same as the original)
    //      default move --> True (this is the same as the original)
    //      default copy --> False (this is different from the original)
    //      copy assignable --> True (this is the different from before)
    //      move assignable --> True (this is the different from before)
}


