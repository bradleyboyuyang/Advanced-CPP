﻿/*
    Level 3.2: STL Algorithms II
    Problem 1: Searching in Numeric Array

    Name: Boyu Yang

    Problem objective:
    a) All the search algorithms search for the location of a value x in a vector v. The return type is a nested
    tuple consisting of a range that encloses x and a Boolean value that indicates success or failure.
    Now implement the same functionality using std::find_if. Remember that the output is in index
    space and you will need std::distance to convert iterators to indexes. Furthermore, create a
    wrapper for std::find to find the index corresponding to a given value in the vector.
    b) Implement the O (log n) algorithms std::lower bound and std::upper bound to effect the same
    functionality as in part a). Again, you need (as always) to create a wrapper function.
    c) Implement the O (log n) algorithm stud::equal range to effect the same functionality as in part b).
    Again, you need (as always) to create a wrapper function.
    d) Test the algorithm stud::find_if_not() using an example of your choice.

*/

#include <iostream>
#include <array>
#include <algorithm>
#include <tuple>
#include <vector>

using Range = std::tuple<std::size_t, std::size_t>;
using Result = std::tuple<Range, bool>;

// converting iterators to indexes 
template <typename T>
int iter_to_index(const std::vector<T>& v, int val) {
    auto it = std::find(v.begin(), v.end(), val);
    return std::distance(v.begin(), it);
};

// result using non std functions 
template <typename T>
Result find_sequential_greater(const std::vector<T>& v, T x) {
    for (std::size_t j = 0; j < v.size(); ++j) {
        if (v[j] <= x && v[j + 1] > x) {
            return std::make_tuple(std::make_tuple(j, j + 1), true);
        }
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
}

// Want to check if the vector is already sequentially sorted 
template <typename T>
bool check_sequential(const std::vector<T>& v, T idx_val, T target) {
    // get index not iterator
    int beg = iter_to_index(v, idx_val);
    int aft = v[beg + 1];
    if (beg <= target && aft > target) {
        return true;
    }
    return false;
}

template <typename T>
Result findif_sequential_greater(const std::vector<T>& v, T x) {
    // checking if sequential 
    auto it_temp = [=](T idx_val) { return check_sequential(v, idx_val, x); };
    auto it = std::find_if(v.begin(), v.end(), it_temp);

    // check if anything was found 
    if (it != v.end()) {
        int index = std::distance(v.begin(), it);
        return std::make_tuple(std::make_tuple(index, index + 1), true);
    }
    return std::make_tuple(std::make_tuple(999, 999), false);

};

// Part B: Using lower / upper bound 

template <typename T>
Result lowerbnd_sequential_greater(const std::vector<T>& v, T x) {
    // checking if sequential
    auto it_lower = std::lower_bound(v.begin(), v.end(), x);
    int idx_lower = std::distance(v.begin(), it_lower);
    if (it_lower != v.end()) {
        T compare = (T)v[idx_lower - 1];
        if (compare <= x) {
            return std::make_tuple(std::make_tuple(idx_lower - 1, idx_lower), true);
        }
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
};

template <typename T>
Result highbnd_sequential_greater(const std::vector<T>& v, T x) {
    // checking if sequential
    auto it_high = std::upper_bound(v.begin(), v.end(), x);
    int idx_high = std::distance(v.begin(), it_high);
    if (it_high != v.end()) {
        T compare = (T)v[idx_high - 1];
        if (compare <= x) {
            return std::make_tuple(std::make_tuple(idx_high - 1, idx_high), true);
        }
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
};



// Part C: equal range 
template <typename T>
Result equal_sequential_greater(const std::vector<T>& v, T x) {
    // checking if sequential
    auto it_eq = std::equal_range(v.begin(), v.end(), x);
    int idx_high = std::distance(v.begin(), it_eq.second);
    if (it_eq.second != v.end()) {
        T compare = (T)v[idx_high - 1];  // typecasting for comparison
        if (compare <= x) {
            return std::make_tuple(std::make_tuple(idx_high - 1, idx_high), true);
        }
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
};

// Part D: find if not function 
// used example from course  
bool isODD(int input) {
    if (input % 2 == 1) {
        return true;
    }
    return false;
}

template <typename T>
Result find_if_not_func(const std::vector<T>& v) {
    auto it = std::find_if_not(v.begin(), v.end(), isODD);
    int idx = std::distance(v.begin(), it);
    if (it != v.end()) {
        return std::make_tuple(std::make_tuple(idx, idx), true);
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
}

// Including print functions to make testing easier 
template <typename T>
void print(std::vector<T>& v) {
    for (auto el : v) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

// range is a tuple so have to use get<>
void print(Result input) {
    auto range = std::get<0>(input);

    std::cout << "Range " << std::get<0>(range) << ", " << std::get<1>(range) << "\n";
    std::cout << "Success: " << std::get<1>(input) << std::endl;
}

int main() {
    /// a) All the search algorithms search for the location of a value x in a vector v. The return type is a nested
    /// tuple consisting of a range that encloses x and a Boolean value that indicates success or failure.
    std::cout << "Part A:" << std::endl;
    std::vector<int> vIn_A = { 1, 2, 8, 9 };

    /// Now implement the same functionality using std::find_if. Remember that the output is in index
    /// space and you will need std::distance to convert iterators to indexes. Furthermore, create a
    /// wrapper for std::find to find the index corresponding to a given value in the vector.
    Result res_A = findif_sequential_greater(vIn_A, 4);
    print(res_A);

    /// b) Implement the O (log n) algorithms std::lower bound and std::upper bound to effect the same
    /// functionality as in part a). Again, you need (as always) to create a wrapper function.
    std::cout << "Part B:" << std::endl;
    Result res_B1 = highbnd_sequential_greater(vIn_A, 4);
    print(res_B1);

    Result res_B2 = lowerbnd_sequential_greater(vIn_A, 4);
    print(res_B2);

    /// c) Implement the O (log n) algorithm stud::equal range to effect the same functionality as in part b).
    /// Again, you need (as always) to create a wrapper function.
    std::cout << "Part C:" << std::endl;
    Result res_C = equal_sequential_greater(vIn_A, 4);
    print(res_C);

    /// d) Test the algorithm stud::find_if_not() using an example of your choice.
    std::cout << "Part D:" << std::endl;
    Result res_D = find_if_not_func(vIn_A);
    print(res_D);
}


