/*
    Level 2.2: Advanced Lambda Programming
    Problem 4: Emulating deprecated C++ 98 STL Bind Code

    Name: Boyu Yang

    Problem objective:
    Implement lambda functions
*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>

using ScalarFunction = std::function<double(const double&)>;

// bind first parameter of a function
template <typename T>
std::function<T(const T&)> bind1st
(const std::function<T(const T& x, const T& y)>& f, const T& x_)
{ // Bind to the first param x of f(x,y)
    return [=](const T& y) mutable {
        return f(x_, y);
    };
}

// bind second parameter of a function
template <typename T>
std::function<T(const T&)> bind2nd
(const std::function<T(const T& x, const T& y)>& f, const T& y_)
{ // Bind to the second param y of f(x,y)
    return [=](const T& x) mutable {
        return f(x, y_);
    };
}

int main() {
    // define the test function fxy
    auto fxy = [](const double& x, const double& y) {return x * 2 + y; };
    double yval = 10.0;
    ScalarFunction fx = bind2nd<double>(fxy, yval); // bind the second argument, the function is fx(t) = 2*t+10
    std::cout << fx(3.0) << std::endl; // the answer should be 3*3 + 10 = 16
    // Test new bind code on STL algorithms
    std::vector<double> vec(10, 2.0); // a vector of length 10 with value 2
    std::transform(vec.begin(), vec.end(), vec.begin(), fx); // each value in the vector is now 2*2+10 = 14
    for (auto i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << ",";
    }

}
