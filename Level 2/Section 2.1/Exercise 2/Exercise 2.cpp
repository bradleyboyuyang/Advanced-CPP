/*
    Level 2.1: Type Traits
    Problem 2: Simple switchable Bridge Functionality

    Name: Boyu Yang

    Problem objective:
    We create a template function that supports both pointers and reference types. If it is a pointer it is 
    dereferenced and then printed while if it is not a pointer type and it is a scalar reference type then it is 
    printed directly. Use the is_pointer() function in conjunction with std::true_type and 
    std::false_type to determine which implementation should be called.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
#include<type_traits>


// We take the method introduced in the class: create two separate functions for the pointer and non-pointer case
template <typename T>
void isPointer(const T& t, std::true_type) {
    // this function is called for a pointer (switch)
    std::cout << "This is a pointer. The value it points to is: " << *t << std::endl;
}

template <typename T>
void isPointer(const T& t, std::false_type) {
    // this function is called for a pointer (switch)
    std::cout << "This is not a pointer. The value is: " << t << std::endl;
}

template <typename T>
void checkPointer(const T& val) {
    isPointer(val, std::is_pointer<T>());
}

int main()
{
    // Use of a switch
    // Test a shared pointer
    std::shared_ptr<int> ival(new int(23));
    checkPointer(ival); // shared pointer is not pointer type, therefore print the address
    checkPointer(ival.get());// the raw pointer
    checkPointer(*ival);

    // Test a raw pointer
    int* ival2 = new int; *ival2 = 10;
    checkPointer(ival2);
    checkPointer(*ival2);
    delete ival2;
    
}


