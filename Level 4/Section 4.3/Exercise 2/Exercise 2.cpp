/*
    Level 4.3: Random Number Generators and Distributions
    Problem 2: Categories of Distributions

    Name: Boyu Yang

    Problem objective:
    In this exercise we write a generic function that works with any distribution and random number engine.
    We also generate a large number of variates of the distribution and we store these values in a map.
    a) Design and implement the above code to generate what is essentially a histogram of values of a distribution.
    b) Test the code by choosing the distributions: geometric, uniform and poisson.
    c) Examine the generated output in each case; does it look like the probability of these distributions?

*/

#include <iostream>
#include <random>
#include <map>
#include <string>

/// a) Design and implement the above code to generate what is essentially a histogram of values of a distribution.
// we use template function to get the generic engine and generic distribution
template <typename Dist, typename Eng>
void GenerateRandomNumbers(Dist d, Eng eng, int NTrials, const std::string& s) {
    // Key = bucket/value; Value = number of occurrences
    std::map<long long, int> counter;
    // count the random number appearances
    for (int i = 0; i < NTrials; ++i) {
        long long value = static_cast<long long>(d(eng));
        ++counter[value];
    }
    // print the distribution
    std::cout << "Distribution: " << s << std::endl;
    for (const auto& entry : counter) {
        std::cout << "Value: " << entry.first << ", Occurrences: " << entry.second << std::endl;
    }
    std::cout << std::endl;
}



int main() {
    /// b) Test the code by choosing the distributions : geometric, uniform and poisson.
    std::mt19937 eng;
    int nTrials = 100000;
    std::geometric_distribution<int> geo_dist(0.4); // geometric with p=0.4
    std::uniform_int_distribution<long> uni_dist(1, 10); // uniform integer from 1 to 100
    std::poisson_distribution<long long> poi_dist(5); // poisson with mean=5
    GenerateRandomNumbers(geo_dist, eng, nTrials, "geometric");
    GenerateRandomNumbers(uni_dist, eng, nTrials, "uniform");
    GenerateRandomNumbers(poi_dist, eng, nTrials, "poisson");

    /// c) Examine the generated output in each case; does it look like the probability of these distributions ?
    // Yes, when the number of trials is large, it looks like the probability of these distributions.


}