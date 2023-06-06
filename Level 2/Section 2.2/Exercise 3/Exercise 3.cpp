/*
    Level 2.2: Advanced Type Traits
    Problem 3: Conversions

    Name: Boyu Yang

    Problem objective:
    Sometimes you may wish to structurally change fundamental properties of types in an application.
    Examples are:
    • Mapping integers to unsigned integers and vice versa.
    • Add/remove the const specifier to or from a type.
    • Add/remove a pointer to or from a type.
    • Add/remove the volatile specifier to or from a type.
    • Discuss the difference between direct list initialisation and copy list initialisation in C++17/20
    compared to C++11. In which case does auto deduction reduce to std::initializer_list?
    Give a code example. Under which circumstances can we get ill-formed expressions?
    • Discuss how Class Template Argument Deduction (CTAD)) reduces code verbosity. Give a non-trivial
    example using std::tuple and a user-defined class.
    • Investigate the applicability of decltype and std::is_same when comparing the type of a result with a
    “target” type.
    Answer the following questions:
    a) Write a separate function for each of the above requirements.
    b) Test the functions on a range of fundamental, scalar, object, arithmetic and compound types.

*/

#include <iostream>
#include <tuple>
#include <vector>
#include <type_traits>
#include <typeinfo>

// a simple function to print the type name of variables
template <typename T>
void print(const T& val) {
    std::cout << "Type " << typeid(val).name() << std::endl;
}

/// Part (A) Write a separate function for each of the above requirements.

/// Mapping integers to unsigned integers and vice versa.

// explicit convert signed integers to unsigned integers
template <typename T>
using SignedType = typename std::make_signed<T>::type;

template <typename T>
using UnsignedType = typename std::make_unsigned<T>::type;

template <typename T>
auto toUnsigned(T value) {
    return static_cast<typename std::make_unsigned<T>::type>(value);
}
// convert unsigned values to signed values
template <typename T>
auto toSigned(T value) {
    return static_cast<typename std::make_signed<T>::type>(value);
}

/// Add/remove the const specifier to or from a type.
template <typename T>
using AddConst = const T;

template <typename T>
using RemoveConst = typename std::remove_const<T>::type;


/// Add/remove a pointer to or from a type.
template <typename T>
using AddPointer = T*;

template <typename T>
using RemovePointer = typename std::remove_pointer<T>::type;


/// Add/remove the volatile specifier to or from a type.
template <typename T>
using AddVolatile = volatile T;

template <typename T>
using RemoveVolatile = typename std::remove_volatile<T>::type;



/// Discuss how Class Template Argument Deduction (CTAD)) reduces code verbosity. Give a non-trivial
/// example using std::tuple and a user-defined class.
// We define a class and use std::tuple in the test code
class MyClass {
public:
    explicit MyClass(int value) : value_(value) {}

    void printValue() const {
        std::cout << "Value: " << value_ << '\n';
    }

private:
    int value_;
};


int main()
{
    /// Part (A) 
    /// Discuss the difference between direct list initialisation and copy list initialisation in C++17/20
    /// compared to C++11. In which case does auto deduction reduce to std::initializer_list?
    /// Give a code example. Under which circumstances can we get ill-formed expressions?
    // Direct List Initialization in C++ 11 
    int integer1{ 123 };
    // use auto in C++17
    auto integer{123};

    int a[3] = { 1,2,3 };
    // Copy, lvalue
    auto [x, y, z] = a; // identifiers must be of the same length

    // for C++ 17 can use auto type and the initalizer_list<> is deduced but all values must be of the same type 
    // If the values are not the same type, we get ill-formed expressions.

    /// Discuss how Class Template Argument Deduction (CTAD)) reduces code verbosity
    // CTAD allows us to create a tuple without explicitly specifying the template arguments for std::tuple. 
    // The constructor arguments are used to deduce the types. This reduces code verbosity and makes the code more readable.
    auto myTuple = std::make_tuple(42, "Hello", MyClass(10));
    std::get<2>(myTuple).printValue();

    /// Investigate the applicability of decltype and std::is_same when comparing the type of a result with a
    /// “target” type.
    auto add = [](int a, int b) {return a + b; };
    decltype(add(1, 2)) result = add(3, 4);
    if (std::is_same<decltype(result), int>::value) {
        std::cout << "Result type is int." << std::endl;
    }
    else {
        std::cout << "Result type is not int." << std::endl;
    }


    /// Part (B) Test the functions on a range of fundamental, scalar, object, arithmetic and compound types
    /// change signed to unsigned and vice versa
    // int types
    int value = -42;
    print(toUnsigned(value));
    print(toSigned(value));
    // short types
    short sht = -10;
    print(toUnsigned(sht));
    print(toSigned(sht));
    // char type
    char chr = -127;
    print(toUnsigned(chr));
    print(toSigned(chr));

    // test fundamental types
    std::cout << std::boolalpha;
    std::cout << "========Fundamental types========" << std::endl;
    std::cout << "Is signed: " << std::is_signed<SignedType<int>>::value << std::endl;
    std::cout << "Is signed: " << std::is_signed<UnsignedType<int>>::value << std::endl;   
    std::cout << "Is const: " << std::is_const<AddConst<int>>::value << std::endl;            
    std::cout << "Is const: " << std::is_const<RemoveConst<const int>>::value << std::endl;
    std::cout << "Is pointer: " << std::is_pointer<AddPointer<int>>::value << std::endl;
    std::cout << "Is pointer: " << std::is_pointer<RemovePointer<int*>>::value << std::endl;
    std::cout << "Is volatile: " << std::is_volatile<AddVolatile<int>>::value << std::endl;
    std::cout << "Is volatile: " << std::is_volatile<RemoveVolatile<volatile int>>::value << std::endl;

    // test scalar types
    std::cout << "========Scalar types========" << std::endl;
    enum Suit { SPADE, HEART, DIAMOND, CLUB };
    std::cout << "Is signed: " << std::is_signed<SignedType<Suit>>::value << std::endl;
    std::cout << "Is signed: " << std::is_signed<UnsignedType<Suit>>::value << std::endl;
    std::cout << "Is const: " << std::is_const<AddConst<Suit>>::value << std::endl;
    std::cout << "Is const: " << std::is_const<RemoveConst<const Suit>>::value << std::endl;
    std::cout << "Is pointer: " << std::is_pointer<AddPointer<Suit>>::value << std::endl;
    std::cout << "Is pointer: " << std::is_pointer<RemovePointer<Suit>*>::value << std::endl;
    std::cout << "Is volatile: " << std::is_volatile<AddVolatile<Suit>>::value << std::endl;
    std::cout << "Is volatile: " << std::is_volatile<RemoveVolatile<volatile Suit>>::value << std::endl;
    // arithmetic types
    std::cout << "========Arithmetic types========" << std::endl;
    std::cout << "Is signed: " << std::is_signed<SignedType<const char>>::value << std::endl;
    std::cout << "Is signed: " << std::is_signed<UnsignedType<const char>>::value << std::endl;
    std::cout << "Is const: " << std::is_const<AddConst<char>>::value << std::endl;
    std::cout << "Is const: " << std::is_const<RemoveConst<const char>>::value << std::endl;
    std::cout << "Is pointer: " << std::is_pointer<AddPointer<const char>>::value << std::endl;
    std::cout << "Is pointer: " << std::is_pointer<RemovePointer<const char*>>::value << std::endl;
    std::cout << "Is volatile: " << std::is_volatile<AddVolatile<const char>>::value << std::endl;
    std::cout << "Is volatile: " << std::is_volatile<RemoveVolatile<volatile const char>>::value << std::endl;

    // object types
    std::cout << "========Object types========" << std::endl;
    std::cout << "Is const: " << std::is_const<AddConst<std::string>>::value << std::endl;
    std::cout << "Is const: " << std::is_const<RemoveConst<const std::string>>::value << std::endl;
    std::cout << "Is pointer: " << std::is_pointer<AddPointer<std::string>>::value << std::endl;
    std::cout << "Is pointer: " << std::is_pointer<RemovePointer<std::string*>>::value << std::endl;
    std::cout << "Is volatile: " << std::is_volatile<AddVolatile<std::string>>::value << std::endl;
    std::cout << "Is volatile: " << std::is_volatile<RemoveVolatile<volatile std::string>>::value << std::endl;


    // compound types
    std::cout << "========Compound types========" << std::endl;
    std::cout << "Is const: " << std::is_const<AddConst<std::vector<int>>>::value << std::endl;
    std::cout << "Is const: " << std::is_const<RemoveConst<const std::vector<int>>>::value << std::endl;
    std::cout << "Is pointer: " << std::is_pointer<AddPointer<std::vector<int>>>::value << std::endl;
    std::cout << "Is pointer: " << std::is_pointer<RemovePointer<std::vector<int>*>>::value << std::endl;
    std::cout << "Is volatile: " << std::is_volatile<AddVolatile<std::vector<int>>>::value << std::endl;
    std::cout << "Is volatile: " << std::is_volatile<RemoveVolatile<volatile std::vector<int>>>::value << std::endl;

}