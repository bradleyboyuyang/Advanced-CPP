#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// function wrapper
template <typename T>
using FunctionType = std::function<T(const T& t)>;

template <typename T>
class NextGenPolymorphism
{
private:
    FunctionType<T> _func;
    T _fac;
public:
    // constructor: initialize the function wrapper
    NextGenPolymorphism(const FunctionType<T>& function, const T& factor) : _fac(factor)
    {
        _func = function;
    }
    T execute(double d) { return _func(d) * _fac; }
    void switchFunction(const FunctionType<T>& function)
    {
        _func = function;
    }
};


//int main()
//{
//    // Next-generation design pattern
//    auto square = [](double d) {return d * d; };
//    auto expo = [](double d) {return std::exp(d); };
//    NextGenPolymorphism<double> ng(square, 1.0);
//    std::cout << "Square: " << ng.execute(2.0) << '\n'; // 4
//    // square is not cool, switch to expo
//    ng.switchFunction(expo);
//    std::cout << "Exponential: " << ng.execute(5.0); // 148.413
//}