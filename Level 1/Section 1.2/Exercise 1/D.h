#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
using Vec = std::vector<T>;

template <typename T> class D {

private:
	Vec<T> vec;
	// copy constructor
	D(const C<T>& source) = delete;
	// assignment operator
	D<T>& operator = (const D<T>& source) = delete;

public:
	// default constructor
	D() = default;

	// constructor
	D(Vec<T> input) : vec(input) {
	std::cout << "call normal constructor" << std::endl;
	}

	// destructor
	~D() {}

	void print() {
		std::cout << "call print function of D" << std::endl;

		for (auto i : vec) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	void scale(double multiplier) noexcept {
		std::cout << "call scale function of D" << std::endl;
		std::for_each(vec.begin(), vec.end(), [multiplier](T& i) {i *= multiplier; });
	}

};