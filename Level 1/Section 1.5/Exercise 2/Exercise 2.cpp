#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <tuple>
#include <complex>

// Recursive case 
template <typename T, typename Tuple, std::size_t N>
struct Calculator
{
    static T calcMax(const Tuple& tup) {
        return std::max(std::get<N - 1>(tup), Calculator<T, Tuple, N-1>::calcMax(tup));
   }

    static T calcSum(const Tuple& tup) {
        return std::get<N - 1>(tup) + Calculator<T, Tuple, N - 1>::calcSum(tup);
    }

    static T calcAvg(const Tuple& tup) {
        return calcSum(tup) / static_cast<T>(N);
    }

};

// ending/base case for recursion (only for max and sum, no need for avg)
template <typename T, typename Tuple>
struct Calculator<T, Tuple, 1>
{
    static T calcMax(const Tuple& tup) {
        return std::get<0>(tup);
    }

    static T calcSum(const Tuple& tup) {
        return std::get<0>(tup);
    }

};

int main()
{
    /// Part (A) Create a template class with static member functions to compute the maximum
    /// sum and average of the elements in the tuple
    // Actually two ways to do this: std::apply or normal recursion way, we implement using the recursive way


    /// Part (B) Test the code on tuples with two and three elements whose underlying type is double
    using Tuple = std::tuple<double, double, double>;
    Tuple tup = std::make_tuple(3.14, 4.31, 1.23);
    const int size = std::tuple_size<decltype(tup)>::value;
    std::cout << "Max: " << Calculator<double, Tuple, size>::calcMax(tup) << std::endl;
    std::cout << "Sum: " << Calculator<double, Tuple, size>::calcSum(tup) << std::endl;
    std::cout << "Avg: " << Calculator<double, Tuple, size>::calcAvg(tup) << std::endl;


    /// Part (C) Compute the sum and average of a tuple whose element type is std::complex<int>
    using Complex = std::complex<int>;
    using ComplexTuple = std::tuple<Complex, Complex, Complex>;
    ComplexTuple tup_com = std::make_tuple(Complex(1, 2), Complex(3, 4), Complex(5, 6));
    const int size_com = std::tuple_size<decltype(tup_com)>::value;
    std::cout << "Sum: " << Calculator<Complex, ComplexTuple, size_com>::calcSum(tup_com) << std::endl;
    std::cout << "Avg: " << Calculator<Complex, ComplexTuple, size_com>::calcAvg(tup_com) << std::endl;
}