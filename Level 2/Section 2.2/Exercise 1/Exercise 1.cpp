/*
    Level 2.2: Advanced Type Traits
    Problem 1: A Numeric Application: the Beginnings of a Vector Space

    Name: Boyu Yang

    Problem objective:
    Let’s pretend that we wish to create a mathematical library to model vector spaces. In particular, we
    define the following operations:
    • Add two vectors.
    • The additive inverse of a vector.
    • Scalar multiplicity (premultiply the vector by a scalar).

*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <type_traits>
#include <complex>

/// Part (A) Define addition of two vectors
// vector addition if it is a compound type
template <typename T>
T Addition_impl(const T& t1, const T& t2, std::true_type) {
    T result; // (t1.size());
    for (auto i = 0; i < t1.size(); ++i) {
        result.push_back(t1[i] + t2[i]);
    }
    return result;
}

// scalar addition if std::false_type
template <typename T>
T Addition_impl(const T& t1, const T& t2, std::false_type) {
    // addition of scalar
    return t1 + t2;
}

// addition function that serves as a bridge function
template <typename T>
T Addition(const T& t1, const T& t2)
{ // Vector space addition
    return Addition_impl(t1, t2, std::is_compound<T>());
}

/// Part (B) Define additive inverse of a vector
// reverse every element if the input is a compound type
template <typename T>
void AdditiveInverse_impl(T& val, std::true_type) {
    // Additive inverse of an array
    for (auto it = val.begin(); it != val.end(); ++it) {
        (*it) = -(*it);
    }
}

template <typename T>
void AdditiveInverse_impl(T& t, std::false_type) {
    // additive inverse of a scalar
    t = -t;
}

// the bridge function
template <typename T>
void AdditiveInverse(T& val)
{ // val -> -val for a scalar or a vector
    AdditiveInverse_impl(val, std::is_compound<T>());
}

/// Part (C) Define a function for scalar multiplication of a scalar and a vector, producing a new vector
// This is similar to Part (A) and (B), yet we have four combinations of types in the base case
// case 1: scalar multiplies scalar
template <typename T1, typename T2>
void Multiplication_impl(const T1& t1, std::false_type, const T2& t2, std::false_type) {
    std::cout << "Please enter a scalar and a vector" << std::endl;
};

// case 2: vector multiplies scalar
template <typename T1, typename T2>
auto Multiplication_impl(const T1& t1, std::true_type, const T2& t2, std::false_type) {
    T1 result(t1);
    std::for_each(result.begin(), result.end(), [t2](auto& i) {i *= t2; });
    return result;
};

// case 3: scalar multiplies vector
template <typename T1, typename T2>
auto Multiplication_impl(const T1& t1, std::false_type, const T2& t2, std::true_type) {
    T2 result(t2);
    std::for_each(result.begin(), result.end(), [t1](auto& i) {i *= t1; });
    return result;
};

// case 4: multiplication with two arrays
template <typename T1, typename T2>
void Multiplication_impl(const T1& t1, std::true_type, const T2& t2, std::true_type) {
    std::cout << "Please enter a scalar and a vector" << std::endl;
};

// the bridge function
template <typename T1, typename T2>
auto Multiplication(const T1& t1, const T2& t2) {
    return Multiplication_impl(t1, std::is_compound<T1>(), t2, std::is_compound<T2>());
};


// print the content of a vector or array
template <typename T>
void print(const T& vec) {
    for (auto it = std::begin(vec); it != std::end(vec); ++it) {
        std::cout << *it << ",";
    }
    std::cout << std::endl;
}

int main()
{
    /// Part (A) Define addition of two vectors
    // test the function "Addition()"
    // addition of two vectors
    std::vector<int> arr3 = { 1,2,3,4 };
    std::vector<int> arr4 = { 10, 20, 30, 40 };
    auto sum = Addition(arr3, arr4);
    print(sum);

    // addition of two scalars
    double x = 1.0; double y = 2.0;
    std::cout << "Addition of numbers: " << Addition(x, y) << std::endl;

    /// Part (B) Define additive inverse of a vector
    // test the function "AdditiveInverse()"
    //invert a scalar
    double d = 1.0;
    AdditiveInverse(d);
    std::cout << "Inverse: " << d << std::endl;
    // invert an array
    std::array<int, 4> arr = { 1,2,3,4 };
    AdditiveInverse(arr); // all the elements will be minus, achieving compile-time polymorphism
    print(arr);

    /// Part (C) Define a function for scalar multiplication of a scalar and a vector, producing a new vector. Determine 
    /// the signature of this function
    // Please check the implementation above

    /// Part (D) Test these three functions for double, std::array<double, N> and std::vector<double>
    double scalar = 5.0;
    std::vector<double> vec = { 5,4,3,2,1 };
    std::array<double, 5> ar = { 3,5,7,9,0 };

    // test for multiplication of double and std::array<double, N>
    print(Multiplication(scalar, ar));

    // test for multiplication of double and std::vector<double>
    print(Multiplication(vec, scalar));

    /// Part (E) Test the functions on containers whose underlying type is std::complex<double>
    double multiplier = 5.5;
    std::complex<double> c1(1, 2);
    std::complex<double> c2(2, 4);
    std::complex<double> c3(3, 5);
    std::complex<double> c4(6, 4);
    std::vector<std::complex<double>> comp1{ c1, c2 };
    std::vector<std::complex<double>> comp2{ c3, c4 };

    // test for addition
    auto compsum = Addition(comp1, comp2);
    print(compsum);

    // test for additive inverse
    AdditiveInverse(compsum);
    print(compsum);

    // test for multiplication
    // it is worth noting that complex number itself is compound type
    print(Multiplication(multiplier, comp1));
}


