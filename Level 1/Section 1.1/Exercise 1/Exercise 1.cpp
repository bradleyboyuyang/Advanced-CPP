#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    /// Part A) Create a lambda function that multiplies each element of an array by a number
    double multiplier{ 3.0 };
    std::vector<double> v{ 1.0, 2.0, 3.0, 4.0, 5.0 };

    // pass by value
    std::for_each(v.begin(), v.end(), [multiplier](double& i) {i *= multiplier; });

    // pass by reference
    std::for_each(v.begin(), v.end(), [&multiplier](double& i) {i *= multiplier; });

    /// Part B) Print values using auto to initialize the iterator variable
    for (auto it = v.begin(); it < v.end(); it++) {
        std::cout << *it << std::endl;
    }

    /// Part C) Write a lambda function that compute the minimum and maximum and return pair/tuple
    v = { 5.0, 3.0, 1.5, 4.5, 10.5 };
    auto calcMinMax = [](std::vector<double> v) -> std::pair<double, double>
    {
        double min = *v.begin();
        double max = *v.begin();
        std::for_each(v.begin(), v.end(), [&](double& i) {min = i < min ? i : min; });
        std::for_each(v.begin(), v.end(), [&](double& i) {max = i > max ? i : max; });
        return std::make_pair(min, max);
    };

    std::cout << "min element: " << calcMinMax(v).first << std::endl;
    std::cout << "max_element: " << calcMinMax(v).second << std::endl;
    

    /// Part D) Compare with std::minmax_element
    auto result = std::minmax_element(v.begin(), v.end());
    std::cout << "min element: " << *result.first << std::endl;
    std::cout << "max_element: " << *result.second << std::endl;

    // We get the same output. The minmax_element method is quite easy to understand and reuse
}

