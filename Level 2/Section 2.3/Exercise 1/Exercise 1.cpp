/*
    Level 2.2: Advanced Lambda Programming
    Problem 1: User-defined deprecated Entities

    Name: Boyu Yang

    Problem objective:
    Since C++14 it is possible to mark C++ entities as being deprecated/obsolete using the C++14 deprecated
    attribute, for example:
    [[deprecated("old stuff")]] void Func() {// whatever}
    Calling this function will result in your program failing to compile. The objective of this exercise is to mark
    a range of entities as being deprecated to (try to) use them in code. Answer the following by marking the
    following entities as being deprecated and testing you code:
    a) Free/global functions.
    b) Deprecated class and non-deprecated class with deprecated member function.
    c) Deprecated global variable.
    d) Deprecated enum and deprecated enum class.
    e) Deprecated template class specialisation.
    f) Deprecated lambda function.
*/

#include <iostream>

/// a) Free / global functions.
[[deprecated("deprecated function")]] 
void deprecatedFunction() {
    std::cout << "This is a random function\n";
}


/// b) Deprecated class and non-deprecated class with deprecated member function.
// deprecated class
class [[deprecated("deprecated class")]] 
    DeprecatedClass {
public:
    DeprecatedClass() = default;
    void func() {
        std::cout << "This is a not a deprecated function\n";
    }

};

// non-deprecated class with deprecated member function
class NonDeprecatedClass
{
public:
    [[deprecated("This member function is deprecated.")]]
    void deprecatedMemberFunction()
    {
        std::cout << "This is a deprecated function\n";
    }
};

/// c) Deprecated global variable.
[[deprecated("This global variable is deprecated.")]]
int deprecatedGlobalVariable = 10;

/// d) Deprecated enumand deprecated enum class.
enum [[deprecated("This enum is deprecated.")]]
DeprecatedEnum
{
    DeprecatedValue1,
    DeprecatedValue2
};

enum class [[deprecated("This enum class is deprecated.")]]
DeprecatedEnumClass
{
    Value1,
    Value2
};

/// e) Deprecated template class specialisation.

template <typename T>
class [[deprecated("This template class specialization is deprecated.")]]
MyDeprecatedTemplateClass {
public:
    MyDeprecatedTemplateClass() = default;
    void func() {
        std::cout << "This is a function of a deprecated template class\n";
    }
};



/// f) Deprecated lambda function.
[[deprecated("This lambda function is deprecated.")]]
auto deprecatedLambda = []()
{
    std::cout << "This is a deprecated lambda function\n";
};

int main()
{
    /// a) Free / global functions.
    //deprecatedFunction(); // "deprecated function"

    /// b) Deprecated class and non-deprecated class with deprecated member function.
    //DeprecatedClass obj1;  // "deprecated class"
    //NonDeprecatedClass obj2;
    //obj2.deprecatedMemberFunction(); // "This member function is deprecated"

    /// c) Deprecated global variable.
    //int x = deprecatedGlobalVariable; // "This global variable is deprecated"

    /// d) Deprecated enumand deprecated enum class.
    //DeprecatedEnum e1 = DeprecatedValue1; // "This enum is deprecated"
    //DeprecatedEnumClass e2 = DeprecatedEnumClass::Value1; // "This enum class is deprecated"

    /// e) Deprecated template class specialisation.
    //MyDeprecatedTemplateClass<int> obj; // "This template class specialization is deprecated"

    /// f) Deprecated lambda function.
    //deprecatedLambda(); // "This lambda function is deprecated"
}


