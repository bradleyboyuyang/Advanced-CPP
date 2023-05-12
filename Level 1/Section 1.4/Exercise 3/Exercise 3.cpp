#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class C
{ // Function object with extra member functions
private:
    double _data;
public:
    C(double data) : _data(data) {}
    double operator () (double factor)
    {
        return _data + factor;
    }
    double translate(double factor)
    {
        return _data + factor;
    }
    double translate2(double factor1, double factor2)
    {
        return _data + factor1 + factor2;
    }
    static double Square(double x)
    {
        return x * x;
    }
};

template <typename T>
using FunctionType = std::function<T(T t)>;

template <typename T>
void print(const FunctionType<T>& f, T t)
{
    std::cout << f(t) << '\n';

}

int main()
{
    using namespace std::placeholders;
    /// Part A) Bind the function wrapper to C’s static member function
    // Since the static member function is shared across all instances, we can evoke the method directly through the class
    FunctionType<double> bindStatic = std::bind(&C::Square, _1);

    /// Part B) Bind the function wrapper to C’s member functions using std::bind and placeholders
    // For non-static functions, we need to use an object of the class to evoke the method
    C obj(123.4);
    FunctionType<double> bindTranslate = std::bind(&C::translate, &obj, _1);
    FunctionType<double> bindTranslate2 = std::bind(&C::translate2, &obj,  _1, 3);

    /// Part C) Test the function
    print(bindStatic, 4.0);
    print(bindTranslate, 4.0);
    print(bindTranslate2, 4.0);


}

