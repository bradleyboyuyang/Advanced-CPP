
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

int main()
{
    // Part A) Create a lambda function that multiplies each element of an array by a number
    double multiplier{ 3.0 };
    vector<double> v{ 1.0, 2.0, 3.0, 4.0, 5.0 };

    // pass by value
    for_each(v.begin(), v.end(), [multiplier](double& i) {i *= multiplier; });

    // pass by reference
    for_each(v.begin(), v.end(), [&multiplier](double& i) {i *= multiplier; });

    // Part B) Print values using auto to initialize the iterator variable
    for (auto i : v) {
        cout << i << endl;
    }

    // Part C) Write a lambda function that compute the minimum and maximum and return pair/tuple
    v = { 5.0, 3.0, 1.5, 4.5, 10.5 };
    auto calcMinMax = [](vector<double> v) -> pair<double, double>
    {
        double min = *v.begin();
        double max = *v.begin();
        for_each(v.begin(), v.end(), [&](double& i) {min = i < min ? i : min; });
        for_each(v.begin(), v.end(), [&](double& i) {max = i > max ? i : max; });
        return make_pair(min, max);
    };

    cout << "min element: " << calcMinMax(v).first << endl;
    cout << "max_element: " << calcMinMax(v).second << endl;
    

    // Part D) Compare with std::minmax_element
    auto result = minmax_element(v.begin(), v.end());
    cout << "min element: " << *result.first << endl;
    cout << "max_element: " << *result.second << endl;

    // We get the same output. The minmax_element method is quite easy to understand and reuse

    return 0;
}

