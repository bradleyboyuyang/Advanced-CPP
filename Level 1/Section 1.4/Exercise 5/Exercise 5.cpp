#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// function wrapper
template <typename T>
using FunctionType = std::function<T(const T& t)>;


// Class hierarchy
template <typename T>
class Shape
{
protected:
    FunctionType<T> _func;
    T _fac;
public:
    Shape() = default; // default constructor
    Shape(const FunctionType<T>& function, const T& factor): _fac(factor) {
        _func = function;
    }
    T rotate(double d) {
        return _func(d) * _fac; // call the protected function wrapper
    }
    void switchFunction(const FunctionType<T>& function)
    {
        _func = function;
    }
};

int main()
{
    /// Part (A) create a single Shape with an embedded command-style function wrapper (such as rotate() or other ones).
    // See the class implementation above


    /// Part (B) Test the new code
    // Test function
    auto square = [](double d) {return d * d; };

    double factor = 4.0;
    double param = 2;
    Shape<double> sp(square, factor);
    std::cout << sp.rotate(param) << std::endl; // output (2*2)*4 = 16

    // switch function, realize polymorphism
    auto expo = [](double d) {return std::exp(d); };
    sp.switchFunction(expo);
    std::cout << sp.rotate(param) << std::endl; // outpur exp(2)*4 = 29.5562

}