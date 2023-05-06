#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <class T> class F {

private:
	T vec;

public:
	// default constructor
	constexpr explicit F() { std::cout << "call default constructor" << std::endl; }
	// constructor
	constexpr explicit F(T input) : vec(input) {
		std::cout << "call normal constructor" << std::endl;
	}
	// copy constructor
	F(const F& source) {
		vec = source.vec;
		std::cout << "call copy constructor" << std::endl;
	}

	// assignment operator
	F& operator = (const F& source) {
		// reload assignment operator for a deep copy
		vec = source.vec;
		std::cout << "call assignment operator" << std::endl;
		return *this;
	}
	// destructor
	~F() {}

	void print() {
		std::cout << "call print function of F" << std::endl;
		for (auto i : vec) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	constexpr void scale(double multiplier) noexcept {
		std::cout << "call scale function of F" << std::endl;
		std::for_each(vec.begin(), vec.end(), [multiplier](auto& i) {i *= multiplier; });
	}

};