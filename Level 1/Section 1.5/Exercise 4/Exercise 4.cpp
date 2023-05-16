#include <iostream>
#include <vector>
#include <algorithm>


template <typename T>
struct IndexSolver {
	static std::size_t findIndex(std::vector<T>& sortedVec, T& x) {

		// we can use STL algorithm `find_if`
		auto idx = std::find_if(sortedVec.begin(), sortedVec.end(), [=](T& d) {return d > x; });

		// Alternative: STL algorithm lower_bound or upper_bound
		// For specification v[i] <= x < v[i + 1], we should use STL `upper_bound`
		// if it is v[i] < x <= v[i + 1], we use STL `lower_bound`
		//auto idx = std::upper_bound(sortedVec.begin(), sortedVec.end(), x);

		// The output index should be decreased by 1 
		if (idx != sortedVec.end()) {
			std::size_t index = std::distance(sortedVec.begin(), idx);
			return index - 1;
		}
		else {
			std::cout << "Index out of range" << std::endl;
			return static_cast<std::size_t>(0);
		}
	}
};

template <typename T>
struct Comparator {
	static 
};




int main()
{
	/// Part (A) Given a sorted numeric vector v and a target value x, find the first index i such that 
	/// v[i] <= x < v[i + 1]. Determine the return type.
	std::vector<int> vec(10);
	for (int i = 0; i < 10; ++i) {
		vec[i] = i * 2 + 5;
	}
	std::cout << "Original Vector: ";
	for (auto val : vec) { std::cout << val << ", "; };
	std::cout << std::endl;
	int x{ 8 };
	std::cout << "Finding value: " << x << " Result Index: " << IndexSolver<int>::findIndex(vec, x) << std::endl;


	/// Part (B) Find the maximum error between two vectors v1 and v2 in a given index range [i; j]
	/// We wish to compute the difference in some(customisable) norm, specifically the absolute error, relative error and
	/// the index values where these errors occur.

	// Ideally, you should use the following C++ functionality if possible:
	//• Move semantics instead of copy constructors.
	//• Smart pointers(if applicable).
	//• Function objectsand lambda functions.
	//• Use as much of STL Algorithms as you can(investigate what’s in the library)


}

