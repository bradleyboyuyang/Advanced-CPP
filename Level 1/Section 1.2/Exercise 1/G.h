#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <class T> class G {

private:
	T vec;

public:
	// default constructor
	constexpr explicit G() { std::cout << "call default constructor" << std::endl; }
	// constructor
	constexpr explicit G(T input) : vec(input) {
		std::cout << "call normal constructor" << std::endl;
	}
	// copy constructor
	G(const G& source) {
		vec = source.vec;
		std::cout << "call copy constructor" << std::endl;
	}

	// assignment operator
	G& operator = (const G& source) {
		// reload assignment operator for a deep copy
		vec = source.vec;
		std::cout << "call assignment operator" << std::endl;
		return *this;
	}
	// destructor
	~G() {}

	void print() {
		std::cout << "call print function of G" << std::endl;
		for (auto i : vec) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	constexpr void scale(double multiplier) noexcept {
		std::cout << "call scale function of G" << std::endl;
		std::for_each(vec.begin(), vec.end(), [multiplier](auto& i) {i *= multiplier; });
	}

};