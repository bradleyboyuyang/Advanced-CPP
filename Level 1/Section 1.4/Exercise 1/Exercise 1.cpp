#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<complex>
#include<functional>
#include<random>

template <typename T>
using FunctionType = std::function<T(const T& t)>;


template <typename T>
void print(const FunctionType<T>& f, T t)
{
    std::cout << f(t) << '\n';
}

// free function
double freeFunc(const double& x) {
    return x * x;
}

// function object
struct funcObj {
    double operator () (const double& x) {
        return x * x;
    }
};

// lambda function
auto MyMultiply = [](auto x) { return x*x; };



int main()
{
    /// Part (A) 
    FunctionType<double> f; // instance of function wrapper


    /// Part (B)
    double test = 15;
    // free function
    f = freeFunc;
    print(f, test);
    // function object
    f = funcObj();
    print(f, test);
    // stored lambda function
    f = MyMultiply;
    print(f, test);
    



}

