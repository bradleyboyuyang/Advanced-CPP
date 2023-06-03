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

/// Part (A)
template <typename T>
void printTypeTrait(const T& t) {
    if (std::is_null_pointer<T>::value)
        std::cout << "This is a null pointer" << std::endl;
    else if (std::is_pointer<T>::value)
        std::cout << "This is a pointer" << std::endl;
    else if (std::is_lvalue_reference<T>::value)
        std::cout << "This is an lvalue reference" << std::endl;
    else if (std::is_rvalue_reference<T>::value)
        std::cout << "This is an rvalue reference" << std::endl;
    else
        std::cout << "This is not a pointer, null pointer, lvalue reference or an rvalue reference" << std::endl;
}


/// Part (B)
template <typename T>
void checkMember(const T& t) {
    if (std::is_member_function_pointer<T>::value)
        std::cout << "This is a member function pointer" << std::endl;
    else if (std::is_member_object_pointer<T>::value)
        std::cout << "This is a pointer to a non-static member object" << std::endl;
    else
        std::cout << "This is neither a member function pointer nor a pointer to a non-static member object" << std::endl;
}


/// Part (C) 
template <typename T>
void IsPointer(const T& t)
{ // First example of type_traits;check if t is a pointer 
// Return type is std::true_type or std::false_type
    if (std::is_pointer<T>::value)
    {
        std::cout << "This is a pointer type argument\n";
    }
    else
    {
        std::cout << "_not_ a pointer type argument\n";
    }
}

int main()
{
    /// Part (A): Test pointer, null pointer, lvalue, rvalue
    int a = 123;
    int* ptr = &a;
    int& lref = a;
    int&& rref = 5;

    printTypeTrait(ptr); // pointer type
    printTypeTrait(nullptr); // null pointer
    printTypeTrait<int&>(lref); // lvalue
    printTypeTrait<int&&>(rref); // rvalue
    printTypeTrait(a); // none of the above

    /// Part (B) check whether a pointer points to static or non-static member
    struct myClass {
        int memberVar;
        void print() {
            std::cout << "call print function" << std::endl;
        }
    };
    checkMember(&myClass::print); // pointer to a member function object
    checkMember(&myClass::memberVar); // pointer to a non-static member object

    /// Part (C) Is a shared pointer a pointer type? Is it a pointer type when converted to raw pointer?
    std::shared_ptr<int> shareptr(new int(42));
    IsPointer(shareptr);
    IsPointer(shareptr.get());
    // It shows that a shared pointer is not a pointer type, yet the raw pointer which it contains is a pointer type.

}


