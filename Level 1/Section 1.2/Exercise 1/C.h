#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
using Vec = std::vector<T>;

template <typename T> class C {

private:
	Vec<T> vec;

public:
	// default constructor
	C() { std::cout << "call default constructor" << std::endl; }
	// constructor
	C(Vec<T> input) : vec(input) {
		std::cout << "call normal constructor" << std::endl;
	}
	// copy constructor
	C(const C<T>& source) {
		vec = source.vec;
		std::cout << "call copy constructor" << std::endl;
	}

	// assignment operator
	C<T>& operator = (const C<T>& source) {
		// reload assignment operator for a deep copy
		vec = source.vec;
		std::cout << "call assignment operator" << std::endl;
		return *this;
	}
	// destructor
	~C() {}

	void print() {
		std::cout << "call print function of C" << std::endl;
		for (auto i : vec) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	void scale(double multiplier) noexcept {
		std::cout << "call scale function of C" << std::endl;
		std::for_each(vec.begin(), vec.end(), [multiplier](T& i) {i *= multiplier; });
	}

};