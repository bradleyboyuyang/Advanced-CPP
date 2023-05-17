#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <tuple>

enum NormType{ABS=1, REL=2};

template <typename T>
struct Solver {
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


	static std::tuple<T, int> calcError(std::vector<T>& v1, std::vector<T>& v2, int i, int j, NormType norm = NormType::ABS)
	{
		int min_len = std::min(v1.size(), v2.size());
		if ((i < 0) || (i > j) || (j > min_len)) {
			std::cout << "Wrong Input" << std::endl;
			return std::make_tuple(-1, -1);
		}
		// Here we use a vector to store the element-wise norm with STL algo. 
		// Although the space complexity can be simplified when using for loop to compare and update max value iteratively.
		
		std::vector<T> diff;
		auto calcAbs = [](T val1, T val2)-> T {return std::abs(val1 - val2); };
		auto calcRel = [](T val1, T val2)-> T {return std::abs((val1 - val2) / val1); };

		switch (norm) {
		case ABS:
			std::transform(v1.begin() + i, v1.begin() + j + 1, v2.begin() + i, std::back_inserter(diff), calcAbs);
			break;
		case REL:
			std::transform(v1.begin() + i, v1.begin() + j + 1, v2.begin() + i, std::back_inserter(diff), calcRel);
			break;
		default:
			std::cout << "Wrong error type. " << std::endl;
			return std::make_tuple(-1, -1);
		}

		auto max_iter = std::max_element(diff.begin(), diff.end());
		int max_idx = std::distance(diff.begin(), max_iter) + i;

		return std::tuple<T, int>(*max_iter, max_idx);
	}
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
	std::cout << "Finding value: " << x << " Result Index: " << Solver<int>::findIndex(vec, x) << std::endl;


	/// Part (B) Find the maximum error between two vectors v1 and v2 in a given index range [i; j]
	/// We wish to compute the difference in some (customisable) norm, specifically the absolute error, relative error and
	/// the index values where these errors occur.
	std::vector<double> vec1(10);
	// we use random number generator
	std::random_device rd;
	std::default_random_engine rng;
	rng.seed(rd());
	std::uniform_real_distribution<double> dis(1, 100);

	for (std::size_t i = 0; i < vec1.size(); ++i) {
		vec1[i] = dis(rng);
	}
	std::vector<double> vec2(10);
	for (std::size_t i = 0; i < vec1.size(); ++i) {
		vec2[i] = dis(rng);
	}

	std::cout << "Vector 1: " << std::endl;
	for (auto& j : vec1) { std::cout << j << " "; }
	std::cout << std::endl;
	std::cout << "Vector 2: " << std::endl;
	for (auto& j : vec2) { std::cout << j << " "; }
	std::cout << std::endl;

	// find max absolute error within a given range
	int i = 3;
	int j = 7;
	auto abs_result = Solver<double>::calcError(vec1, vec2, i, j, NormType::ABS);
	std::cout << "Max absolute error: " << std::get<0>(abs_result) << ", Target Index: " << std::get<1>(abs_result) << std::endl;
	auto rel_result = Solver<double>::calcError(vec1, vec2, i, j, NormType::REL);
	std::cout << "Max relative error: " << std::get<0>(rel_result) << ", Target Index: " << std::get<1>(rel_result) << std::endl;

}

