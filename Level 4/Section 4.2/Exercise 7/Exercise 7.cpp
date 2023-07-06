/*
    Level 3.2: STL Algorithms II
    Problem 7: Mutating Algorithms

    Name: Boyu Yang

    Problem objective:
    Mutating algorithms rearrange the elements of a container in some way without modifying the values. We
    consider the container S = {1,-1,7,8,9,10} for convenience and to keep focused on a specific case.
    Answer the following questions:
    a) Reverse S as a modifier option and copy to a second container.
    b) Rotate S so that the value 8 is the beginning of the container.
    c) Write a function to compute the power set of S (that is, the set of all subsets of S containing 64 elements).
    d) Move the subset {8,9,10} to the front of the container.
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

std::vector<std::vector<int>> powerSet(const std::vector<int>& S) {
    std::vector<std::vector<int>> powerSet;
    int setSize = S.size();
    int numSubsets = pow(2, setSize);

    for (int i = 0; i < numSubsets; i++) {
        std::vector<int> subset;
        for (int j = 0; j < setSize; j++) {
            if ((i & (1 << j)) != 0) {
                subset.push_back(S[j]);
            }
        }
        powerSet.push_back(subset);
    }

    return powerSet;
}

// a generic print function for more general containers
template <typename T, template <typename S, typename Alloc> class Container, typename TAlloc>
void print(const Container<T, TAlloc>& container, const std::string& comment) {
    std::cout << comment << ": ";
    std::for_each(container.begin(), container.end(), [](const T& t) {std::cout << t << ", "; });
    std::cout << std::endl;
}

int main() {
    /// a) Reverse S as a modifier option and copy to a second container.
    std::vector<int> s = { 1, -1, 7, 8, 9, 10 };
    print(s, std::string("original vector"));

    std::vector<int> s_inv;
    std::reverse_copy(s.begin(), s.end(), std::back_inserter(s_inv));
    print(s_inv, std::string("Reversed vector while copying"));

    /// b) Rotate S so that the value 8 is the beginning of the container.
    auto it = std::find(s.begin(), s.end(), 8);
    std::rotate(s.begin(), it, s.end());
    print(s, std::string("vector after rotation (8)"));


    /// c) Write a function to compute the power set of S(that is, the set of all subsets of S containing 64 elements).
    std::vector<std::vector<int>> result = powerSet(s);
    std::cout << "all subsets:\n";
    for (const std::vector<int>& subset : result) {
        std::cout << "{ ";
        for (int num : subset) {
            std::cout << num << " ";
        }
        std::cout << "}" << ", ";
    }
    std::cout << std::endl;

    /// d) Move the subset{ 8,9,10 } to the front of the container.
    std::vector<int> Snew = { 1, -1, 7, 8, 9, 10 };
    auto rotated = std::find(Snew.begin(), Snew.end(), 8);  // find where subset begins
    std::rotate(Snew.begin(), rotated, Snew.end());  // rotate vector so 8 9 10 is at front
    print(s, std::string("vector after rotation (8,9,10)"));


}
