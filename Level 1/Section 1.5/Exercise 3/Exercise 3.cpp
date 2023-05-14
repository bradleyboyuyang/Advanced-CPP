#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <tuple>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/assign.hpp>

// function that computes basic statistics
// use template to accept both std::vector and boost::numeric::ublas::vector
template <typename T, typename Tuple, std::size_t N, typename Vector = std::vector<T>> //template template parameter
Tuple Arithmetic(const Vector& vec) {
    T mean = 0;
    T mean_deviation = 0;
    T range = 0;
    T variance = 0;
    T std;

    // calculate the mean
    std::for_each(vec.begin(), vec.end(), [&](T j) {mean += j; });
    mean /= static_cast<T>(N);

    // calculate the mean deviation
    std::for_each(vec.begin(), vec.end(), [&](T j) {mean_deviation += std::abs(j-mean); });
    mean_deviation /= static_cast<T>(N);

    // calculate min and max
    auto minmax = std::minmax_element(vec.begin(), vec.end());
    range = *minmax.second - *minmax.first;
   
    // calculate variance
    std::for_each(vec.begin(), vec.end(), [&](double j) {variance += std::pow(j - mean, 2); });
    variance /= static_cast<T>(N);

    // standard deviation
    std = std::sqrt(variance);

    return std::make_tuple(mean, mean_deviation, range, std, variance);

}


// function that computes median and smallest mode for a sorted vetor
//use template to accept both std::vector and boost::numeric::ublas::vector
template <typename T, typename Tuple, std::size_t N, typename Vector=std::vector<T>> // template template parameter
Tuple computeMedianAndMode(const Vector& Vec) {
    T median;
    std::vector<T> mode; // there can be more than one mode so we use a vector

    // compute median
    Vector sortedVec = Vec;
    std::sort(sortedVec.begin(), sortedVec.end());
    if (static_cast<int>(N) % 2 == 0) {
        median =(sortedVec[static_cast<int>(N) / 2 - 1] + sortedVec[static_cast<int>(N) / 2]) / 2.0;
    }
    else {
        median = sortedVec[static_cast<int>(N) / 2];
    }

    // compute mode
    std::map<T, std::size_t> countMap;
    for (const T& element : sortedVec) {
        countMap[element]++;
    }
    // get the max frequency
    auto maxVal = std::max_element(countMap.begin(), countMap.end(),
        [](const auto& pair1, const auto& pair2) {
            return pair1.second < pair2.second;
        });
    // get all the mode
    for (const auto& pair : countMap) {
        if (pair.second == maxVal->second) {
            mode.push_back(pair.first);
        }
    }
    // pick the smallest one
    auto smallest_mode = std::min_element(mode.begin(), mode.end());

    return std::make_tuple(median, *smallest_mode);

}


// print elements in a tuple
template <std::size_t index, typename... Args>
void printTuple(const std::tuple<Args...>& pack) {
    if constexpr (index < sizeof...(Args)) {
        std::cout << std::get<index>(pack) << std::endl;
        printTuple<index + 1>(pack);
    }
}

int main()
{
    /// Part (A) Create a function that returns mean, mean deviation, range, std, variance of a numeric vector as a tuple
    // See the function Arithmetic as above


    /// Part (B) Test the function from part a), can use tied variables and std::ignore
    // test std::vector
    using Tuple1 = std::tuple<double, double, double, double, double>;
    std::vector<double> vec1{ 1.45, 3.67, 7.45, 3.55, 2.88 };
    std::cout << "STL Vector Statistics: " << std::endl;
    double mean1, range1, std1;
    std::tie(mean1, std::ignore, range1, std1, std::ignore) = Arithmetic<double, Tuple1, 5>(vec1);
    std::cout << "Mean: " << mean1 << " Range: " << range1 << " Standard deviation: " << std1 << std::endl;
    //printTuple<0>(Arithmetic<double, Tuple1>(vec1)); // directly print all the tuple elements

    //// test boost::numeric::ublas::vector
    std::cout << "STL Vector Statistics: " << std::endl;
    boost::numeric::ublas::vector<double> vec2(5, 3);
    // initialize
    for (int i = 0; i < vec2.size(); i++)
        vec2[i] = i * 2 + 1;
    double mean2, range2, std2;
    std::tie(mean2, std::ignore, range2, std2, std::ignore) = Arithmetic<double, Tuple1, 5>(vec2);
    std::cout << "Mean: " << mean2 << " Range: " << range2 << " Standard deviation: " << std2 << std::endl;
    //printTuple<0>(Arithmetic<double, Tuple1>(vec2)); // directly print all the tuple elements

    /// Part (C) Write a function that computes the median and smallest mode of a vector
    using Tuple2 = std::tuple<double, double>;
    std::vector<double> vec3{ 78,74,68,76,80,84,50,93,55,76,58,74,75 };
    auto mean_mode = computeMedianAndMode<double, Tuple2, 13>(vec3);
    std::cout << "Median: " << std::get<0>(mean_mode) << " Mode: " << std::get<1>(mean_mode) << std::endl;

    std::vector<double> vec4{ 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 6, 6, 6, 7 };
    auto mean_mode2 = computeMedianAndMode<double, Tuple2, 16>(vec4);
    std::cout << "Median: " << std::get<0>(mean_mode2) << " Mode: " << std::get<1>(mean_mode2) << std::endl;


}