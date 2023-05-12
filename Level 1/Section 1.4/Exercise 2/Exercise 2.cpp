#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

double freeFunction3(double x, double y, double z)
{
    return x + y + z;
}


int main()
{
    /// Part A) Define functions of arity 3, 2, 1 and 0 based on the above function
    using namespace std::placeholders;

    // arity 0, equivalent to [](){return freeFunction(5,6,7);}
    auto bind3_func = std::bind(freeFunction3, 5, 6, 7);
    // arity 1, equivalent to [](double x){return freeFunction(x,6,7);}
    auto bind2_func = std::bind(freeFunction3, _1, 6, 7);
    // arity 2, equivalent to [](double x, double y){return freeFunction(x,y,7);}
    auto bind1_func = std::bind(freeFunction3, _1, _2, 7);
    // arity 3, equivalent to [](double x, double y, double z){return freeFunction(x,y,z);}
    auto bind0_func = std::bind(freeFunction3, _1, _2, _3);

    /// Part B) Test these functions by binding the appropriate variables and checking that the output is correct
    std::cout << bind0_func(5, 6, 7) << std::endl;
    std::cout << bind1_func(5, 6) << std::endl;
    std::cout << bind2_func(5) << std::endl;
    std::cout << bind3_func() << std::endl;



}