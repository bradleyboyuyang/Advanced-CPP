#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <class T> class C {

private:
	T vec;

public:
	// default constructor
	C() { std::cout << "call default constructor" << std::endl; }
	// normal constructor
	C(T input) : vec(input) {
		std::cout << "call normal constructor" << std::endl;
	}
	// copy constructor
	C(const C& source) {
		vec = source.vec;
		std::cout << "call copy constructor" << std::endl;
	}

	// assignment operator
	C& operator = (const C& source) {
		// reload assignment operator for a deep copy
		vec = source.vec;
		std::cout << "call assignment operator" << std::endl;
		return *this;
	}

	// move constructor, called when the input is a mutable rvalue
	C(C&& source) {
		vec = std::move(source.vec);
		std::cout << "call move constructor" << std::endl;
	}


	// move assignment operator
	C& operator = (C&& source) {
		vec = std::move(source.vec);
		std::cout << "call move assignment operator" << std::endl;
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