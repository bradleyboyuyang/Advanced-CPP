/*
    Level 3.4: C++11 Tasks
    Problem 5: Loop-Level Parallelism with Tasks

    Name: Boyu Yang

    Problem objective:
    The objective of this exercise is compute reduction/aggregated variables relating to numerical array. In
    order to scope the problem we focus on summing the values of numeric arrays using the so-called
    accumulate function. The main requirements are speedup improvements and serial equivalence (this
    means that the multi-threaded solution gives the same results as the single-threaded solution). We start
    with a single-threaded solution and we incrementally move to multi-threaded solutions based on various
    parallel design patterns.
    a) Create a huge numeric array and sum its elements using std::accumulate(). Measure processing time.
    b) We create an algorithm to parallelise the code in part a). To this end, we split the index space into two
    halves; the right half is run in an asynchronous task while the left part constitutes a recursive call to the
    algorithm for the appropriate index range. If the size of the array is less than 1000 we then side-track
    parallel processing by calling std::accumulate() directly.
    c) Measure the speedup of the code in part b).
    d) Compare the speedup with that achieved by using OpenMP.
    e) Now use threads instead of tasks in order to perform accumulation. Compare speedup.
    f) Write parallel code that use std::accumulate() with a binary function as last parameter. Test the
    algorithm by computing the product of the elements of an array.
    g) Compare performance improvements by using the new parallel features in C++. We focus on three STL
    algorithms (or algorithms of your choice) as applied to std::vector, namely: std::transform, std::sort,
    std::find.
    Answer the following questions:
    • For a vector of a given size N (say N = 10’000’000) compute the running time of these
    algorithms in the sequential and parallel versions.
    • Measure the running times for a range of values of N. Can you find the speedup?[CT1]

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <future>
#include <thread>
#include <execution> // parallel extention in C++ 20 
#include <omp.h>

// Simple function that measures processing time of a function, use variadic template to pass function parameters
template <typename TFunc, typename... Args> void RunAndMeasure(const char* title, TFunc func, Args... args) {
    const auto start = std::chrono::steady_clock::now();
    auto ret = func(args...); // pass the parameter pack
    const auto end = std::chrono::steady_clock::now();
    std::cout << title << ": " << std::chrono::duration<double, std::milli>(end - start).count() << " ms, res " << ret << std::endl;
}


/// a) naive std::accumulate
auto accSum = [](const std::vector<double>& vec) {return std::accumulate(vec.begin(), vec.end(), 0.0); };

/// b) We create an algorithm to parallelise the code in part a). To this end, we split the index space into two
/// halves; the right half is run in an asynchronous task while the left part constitutes a recursive call to the
/// algorithm for the appropriate index range. If the size of the array is less than 1000 we then side-track
/// parallel processing by calling std::accumulate() directly.
// parallel summation with half asynchronous and half recursive
double parallelSum(const std::vector<double>& vec, int left, int right) {
    // a recursive algo: if the size of array is less than 1000 we side-track parallel processing by directly std::accumulate
    // stopping condition
    if ((right - left <= 1000) || (left-right)/2 < left) {
        return std::accumulate(vec.begin() + left, vec.begin() + right, 0.0);
    }
    
    // split the index into two halves
    // the right half is run in an asynchronous task
    std::future<double> rightSum = std::async(std::launch::async, parallelSum, std::ref(vec), (right-left)/2, right);
    
    // the left part recursively call to the algorithm for appropriate index range
    double leftSum = parallelSum(vec, left, (right-left)/2);
    return leftSum + rightSum.get();
}


/// d) Compare the speedup with that achieved by using OpenMP.
// Given code
double OpenMPCalc(const std::vector<double>& vec) {
    omp_set_num_threads(2);
    double sum = 0;
#pragma omp parallel for reduction (+:sumParallel)
    for (std::size_t i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    return sum;
}

/// e) Now use threads instead of tasks in order to perform accumulation. Compare speedup.
double calcSumThread(const std::vector<double>& vec) {
    // number of threads used
    const int numThreads = 4;
    double sumParallel = 0;
    // create a thread group
    std::vector<std::thread> threads(numThreads);
    // for each thread, we compute the sum of a divided part of indices
    for (int i = 0; i < numThreads; ++i) {
        int start = i * (vec.size() / numThreads);
        int end = (i + 1) * (vec.size() / numThreads);
        // Create a promise and its future (can also use packaged_task, etc.)
        // Since thread function cannot return value, to avoid changing the original function, we use std::future to 
        // retrieve the return value from each thread and sum them up. Since the problem requires using threads, 
        // we can use promise/packaged_task to achieve multi-threading rather than direct std::launch::async which cannot use multi-threads
        std::promise<double> p;
        std::future<double> f = p.get_future();
        // We use a separate function to set the promise value equal to the partial summation
        // An alternative would be directly use std::accumulate with parameter index start and end, here for simplicity
        // we simply call our parallel program in (b).
        threads[i] = std::thread{ [&]() {p.set_value(parallelSum(std::ref(vec), start, end)); }};
        sumParallel += f.get();
    }
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }
    return sumParallel;
}

/// f) Write parallel code that use std::accumulate() with a binary function as last parameter. Test the
/// algorithm by computing the product of the elements of an array.
// we use exactly the same parallel program as b) but replace te last parameter of std::accumulate with a binary product function
double parallelProduct(const std::vector<double>& vec, int left, int right) {
    // a recursive algo: if the size of array is less than 1000 we side-track parallel processing by directly std::accumulate
    // stopping condition
    if ((right - left <= 1000) || (left - right) / 2 < left) {
        return std::accumulate(vec.begin() + left, vec.begin() + right, 1.0, [](auto x, auto y) {return x * y; });
    }

    // split the index into two halves
    // the right half is run in an asynchronous task
    std::future<double> rightProduct = std::async(std::launch::async, parallelProduct, std::ref(vec), (right - left) / 2, right);

    // the left part recursively call to the algorithm for appropriate index range
    double leftProduct = parallelProduct(vec, left, (right - left) / 2);
    return leftProduct * rightProduct.get(); // now the recursive relation becomes product
}



int main() {
    /// a) Create a huge numeric array and sum its elements using std::accumulate(). Measure processing time.
    const int N = 10'000'000; // array size
    std::vector<double> vec(N, 1.00001);
    RunAndMeasure("std::accumulate", accSum, vec);
    
    /// c) Measure the speedup of the code in part b).
    RunAndMeasure("Parallel algo to calculate sum", parallelSum, std::ref(vec), 0, N);

    /// d) Compare the speedup with that achieved by using OpenMP.
    RunAndMeasure("OpenMP speedup accumulate", OpenMPCalc, vec);
    
    /// e) Now use threads instead of tasks in order to perform accumulation. Compare speedup.
    RunAndMeasure("Use threads to speedup", calcSumThread, vec);

    /// f) Write parallel code that use std::accumulate() with a binary function as last parameter. Test the
    /// algorithm by computing the product of the elements of an array.
    RunAndMeasure("Parallel computing product", parallelProduct, vec, 0, N);

    /// g) Compare performance improvements by using the new parallel features in C++. We focus on three STL
    /// algorithms (or algorithms of your choice) as applied to std::vector, namely: std::transform, std::sort, std::find.
    // we create an integer vector with random numbers spread out to test our algorithms
    std::vector<int> v(N);
    std::mt19937 gen(42); // seed 42
    std::uniform_int_distribution<int> dis(1, 1000); 
    for (int i = 0; i < N; ++i) {
        v[i] = dis(gen); 
    }
    
    // STL reduce: sequential vs parallel
    RunAndMeasure("std::reduce, seq", [&v] {
        return std::reduce(std::execution::seq, v.begin(), v.end(), 0.0);
    });
    RunAndMeasure("std::reduce, par", [&v] {
        return std::reduce(std::execution::par, v.begin(), v.end(), 0.0);
    });
    RunAndMeasure("std::reduce, par_unseq", [&v] {
        return std::reduce(std::execution::par_unseq, v.begin(), v.end(), 0.0);
    });

    // STL transform: sequential vs parallel
    RunAndMeasure("std::transform, seq", [&v] {
        std::transform(std::execution::seq, v.begin(), v.end(), v.begin(), [](double i) {return i * 2; });
        return 0;
    });

    RunAndMeasure("std::transform, par", [&v] {
        std::transform(std::execution::par, v.begin(), v.end(), v.begin(), [](double i) {return i * 2; });
        return 0;
    });

    // STL sort: sequential vs parallel
    RunAndMeasure("std::sort, seq", [&v] {
        std::sort(std::execution::seq, v.begin(), v.end());
        return 0;
    });

    RunAndMeasure("std::sort, par", [&v] {
        std::sort(std::execution::par, v.begin(), v.end());
        return 0;
    });

    // STL find: sequential vs parallel
    RunAndMeasure("std::find, seq", [&v] {
        auto res = std::find(std::execution::seq, v.begin(), v.end(), 88);
        int distance = std::distance(v.begin(), res);
        return distance;
    });
    RunAndMeasure("std::find, par", [&v] {
        auto res = std::find(std::execution::par, std::begin(v), std::end(v), 88);
        return std::distance(v.begin(), res);
    });
    // Compare all sequential running time and the parallel ones, we can observe significant speed up.
}