#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
using Vec = std::vector<T>;

template <typename T> class E {

private:
	Vec<T> vec;

public:
	// default constructor
	explicit E() { std::cout << "call default constructor" << std::endl; }
	// constructor
	explicit E(Vec<T> input) : vec(input) {
		std::cout << "call normal constructor" << std::endl;
	}
	// copy constructor
	E(const E<T>& source) {
		vec = source.vec;
		std::cout << "call copy constructor" << std::endl;
	}

	// assignment operator
	E<T>& operator = (const E<T>& source) {
		// reload assignment operator for a deep copy
		vec = source.vec;
		std::cout << "call assignment operator" << std::endl;
		return *this;
	}
	// destructor
	~E() {}

	void print() {
		std::cout << "call print function of E" << std::endl;
		for (auto i : vec) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	void scale(double multiplier) noexcept {
		std::cout << "call scale function of E" << std::endl;
		std::for_each(vec.begin(), vec.end(), [multiplier](T& i) {i *= multiplier; });
	}

};