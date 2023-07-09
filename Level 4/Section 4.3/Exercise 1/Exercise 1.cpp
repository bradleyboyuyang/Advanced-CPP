/*
    Level 4.3: Random Number Generators and Distributions
    Problem 1: First 101 Example

    Name: Boyu Yang

    Problem objective:
    This exercise is meant to get you acquainted with the syntax of random number generation in C++11. It is
    an improvement on Boost Random syntax as the classes are now function objects. We first give some
    representative code. In general, the steps are usually the same in all cases:
    Create a random number engine eng.
    Create a distribution d.
    Use the function call operator () to create a variate of the distribution, d(eng).
    a) Copy and adapt this code by using the engine std::linear_congruential_engine and the engine
    adapter with predefined parameters std::mt19937 and std::mt19937_64.
    b) Adapt the code in a) so that it works with the following distributions: Normal, chi-squared, Bernoulli
    and Cauchy.
    c) Write a generic function to generate a list of random numbers for a generic engine and a generic
    distribution. Test the examples from parts a) and b) on this new function.

*/

#include <iostream>
#include <random>

/// c) Write a generic function to generate a list of random numbers for a generic engine and a generic
/// distribution. Test the examples from parts a) and b) on this new function.
// we use template function to get the generic engine and generic distribution
template <typename Engine, typename Distribution>
void generateRandomNumbers(Engine& engine, Distribution& distribution, int nTrials) {
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << distribution(engine) << ", ";
    }
    std::cout << "end\n\n";
}



int main() {
    /// a) Copy and adapt this code by using the engine std::linear_congruential_engine and the engine
    /// adapter with predefined parameters std::mt19937 and std::mt19937_64.
    std::cout << "Part (A)\n";
    // linear_congruential_engine engine
    std::linear_congruential_engine<unsigned int, 16807, 0, 2147483647> eng; 
    // Generate uniform random variates in interval [A, B]
    double A = 0.0;
    double B = 1.0;
    std::uniform_real_distribution<double> dist(A, B);
    int nTrials = 30;
    for (int i = 1; i <= nTrials; ++i)
    { // Produce a number of uniform variates
        std::cout << dist(eng) << ", ";
    }
    std::cout << "end\n\n";
    // Engine adapter with predefined parameters (mt19937)
    std::mt19937 eng2;
    for (int i = 1; i <= nTrials; ++i)
    { // Produce a number of uniform variates
        std::cout << dist(eng2) << ", ";
    }
    std::cout << "end\n\n";


    /// b) Adapt the code in a) so that it works with the following distributions: Normal, chi-squared, Bernoulli and Cauchy.
    std::cout << "Part (B)\n";
    std::chi_squared_distribution<double> chi2_dist(2); // chi-square with df=2
    std::normal_distribution<double> normal_dist(A, B); // normal with mean=0, std=1
    std::bernoulli_distribution ber_dist(0.5); // bernoulli with p=0.5
    std::cauchy_distribution<double> cauchy_dist(A, B); // cauchy with mean=0, std=1

    // use mt19937_64 engine adapter
    std::mt19937_64 en;

    std::cout << "chi2: ";
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << chi2_dist(en) << ", ";
    }
    std::cout << "end\n\n";

    std::cout << "normal: ";
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << normal_dist(en) << ", ";
    }
    std::cout << "end\n\n";

    std::cout << "bernoulli: ";
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << ber_dist(en) << ", ";
    }
    std::cout << "end\n\n";

    std::cout << "cauchy: ";
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << cauchy_dist(en) << ", ";
    }
    std::cout << "end\n\n";


    /// c) Write a generic function to generate a list of random numbers for a generic engine and a generic
    /// distribution. Test the examples from parts a) and b) on this new function.
    std::cout << "Part (C)\n";
    // Test code with various distributions and random engines
    generateRandomNumbers(en, chi2_dist, nTrials);
    generateRandomNumbers(eng, ber_dist, nTrials);
    generateRandomNumbers(eng2, cauchy_dist, nTrials);
    generateRandomNumbers(eng2, normal_dist, nTrials);

}