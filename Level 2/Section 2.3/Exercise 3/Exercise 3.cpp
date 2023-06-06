/*
    Level 2.2: Advanced Lambda Programming
    Problem 3: Doing Mathematics in C++

    Name: Boyu Yang

    Problem objective:
    In this exercise you build a simple vector space of functions. The basic objective is to show how to create
    higher-order functions in C++. It shows what is possible with lambda functions and the possible
    applications to mathematics, engineering and numeric computation in general.
    We scope the problem drastically; we consider only functions of a single variable returning a scalar value.
    All underlying types are double.
    a) Create functions to add, multiply and subtract two functions. Create unary additive inverse of a
    function and a function representing scalar multiplication.
    b) Create trigonometric and other functions such as those in <cmath>. 
    Implement the following functions: cos, sin, tan, exp, log, abs and sqrt.
    c) Finally, produce code that allows you to do min, max
*/

#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <cmath>

/// a) Create functions to add, multiply and subtract two functions. Create unary additive inverse of a
/// function and a function representing scalar multiplication.
using ScalarFunction = std::function<double(const double&)>;

template <typename R, typename D>
using FunctionType = std::function<R(const D&)>;

// add two functions
template <typename R, typename D>
FunctionType<R, D> operator + (const FunctionType<R, D>& f, const FunctionType<R, D>& g)
{ // Addition of functions
    return [=](const D& x)
    {
        return f(x) + g(x);
    };
}

// subtract two functions
template <typename R, typename D>
FunctionType<R, D> operator - (const FunctionType<R, D>& f, const FunctionType<R, D>& g)
{ 
    return [=](const D& x)
    {
        return f(x) - g(x);
    };
}

// multiplicate two functions
template <typename R, typename D>
FunctionType<R, D> operator*(const FunctionType<R, D>& f, const FunctionType<R, D>& g)
{
    return [=](const D& x) {
        return f(x) * g(x);
    };
}

// multiplicate scalar and a function
template <typename R, typename D>
FunctionType<R, D> operator*(const double& scalar, const FunctionType<R, D>& f)
{
    return [=](const D& x) {
        return scalar * f(x);
    };
}

// divide two functions
template <typename R, typename D>
FunctionType<R, D> operator/(const FunctionType<R, D>& f, const FunctionType<R, D>& g)
{
    return [=](const D& x) {
        return f(x) / g(x);
    };
}

// unary additive inverse of a function
template <typename R, typename D>
FunctionType<R, D> operator-(const FunctionType<R, D>& f)
{
    return [=](const D& x) {
        return -f(x);
    };
}

// composite two functions
template <typename R, typename D>
FunctionType<R, D> operator << (const FunctionType<R, D>& f, const FunctionType<R, D>& g)
{
    return [=](const D& x) {
        return f(g(x));
    };
}

/// b) Create trigonometric and other functions such as those in <cmath>. 
/// Implement the following functions: cos, sin, tan, exp, log, abs and sqrt.
// cosine function
template <typename R, typename D>
FunctionType<R, D> cos(const FunctionType<R, D>& f)
{
    return [=](const D& x) {
        return std::cos(f(x));
    };
}
// sine function
template <typename R, typename D>
FunctionType<R, D> sin(const FunctionType<R, D>& f)
{
    return [=](const D& x) {
        return std::sin(f(x));
    };
}
// tangent function
template <typename R, typename D>
FunctionType<R, D> tan(const FunctionType<R, D>& f)
{
    return [=](const D& x) {
        return std::tan(f(x));
    };
}
// exponential function
template <typename R, typename D>
FunctionType<R, D> exp(const FunctionType<R, D>& f)
{
    return [=](const D& x) {
        return std::exp(f(x));
    };
}
// natural log function
template <typename R, typename D>
FunctionType<R, D> log(const FunctionType<R, D>& f)
{
    return [=](const D& x) {
        return std::log(f(x));
    };
}
// absolute function
template <typename R, typename D>
FunctionType<R, D> abs(const FunctionType<R, D>& f)
{
    return [=](const D& x) {
        return std::abs(f(x));
    };
}
// square root function
template <typename R, typename D>
FunctionType<R, D> sqrt(const FunctionType<R, D>& f)
{
    return [=](const D& x) {
        return std::sqrt(f(x));
    };
}

/// c) Finally, produce code that allows you to do min, max
template <typename R, typename D>
FunctionType<R, D> min(const FunctionType<R, D>& f, const FunctionType<R, D>& g)
{   // calculate minimum of two functions
    return [=](const D& x) {
        return std::min(f(x), g(x));
    };
}

template <typename R, typename D>
FunctionType<R, D> max(const FunctionType<R, D>& f, const FunctionType<R, D>& g)
{   // calculate maximum of two functions
    return [=](const D& x) {
        return std::max(f(x), g(x));
    };
}

int main()
{
    /// a) Create functions to add, multiply and subtract two functions. Create unary additive inverse of a
    /// function and a function representing scalar multiplication.
    // Scalar functions: double to double
    ScalarFunction f = [](double x) {return x * x; };
    ScalarFunction g = [=](double x) { return x; };
    std::cout << g(2) << ", " << g(8) << "*";
    // Set I: Arithmetic functions
    double scale = 2.0;
    auto fA = 2.0 * (f + g);
    auto fM = f - g;
    auto fD = f / g;
    auto fMul = f * g;
    auto fC = g << g << 4.0 * g; // Compose
    auto fMinus = -(f + g);
    double x = 5.0;
    std::cout << fA(x) << ", " << fM(x) << ", " << fD(x) << ", "
        << fMul(x) << ", compose: " << fC(x) << ", " << fMinus(x);

    /// b) Create trigonometric and other functions such as those in <cmath>. 
    /// Implement the following functions: cos, sin, tan, exp, log, abs and sqrt.
    auto ftmp = log(g); auto ftmp2 = cos(f);
    auto f2 = (abs(exp(g)) * log(g) + sqrt(ftmp)) / ftmp2;
    std::cout << f2(x) << std::endl;

    /// c) Finally, produce code that allows you to do min, max
    auto h1 = min(f, g);
    auto h2 = max(f, g);
    std::cout << "min(f,g): " << h1(2.0) << '\n';
    std::cout << "max(f,g): " << h2(2.0) << '\n';
    auto h3 = min(h1, max(2 * f, 3 * g));
    auto h4 = max(h2, max(-2 * f, 3 * g));

}

