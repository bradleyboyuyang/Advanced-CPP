#include <iostream>
#include <vector>
#include <algorithm>


template <typename T> class C {
private:
	std::vector<double> vec;

public:
	// default constructor
	C() { std::cout << "default constructor" << std::endl; }
	// constructor
	C(const std::vector<T> input) {
		vec(input);
		std::cout << "constructor" << std::endl;
	}

	// copy constructor
	C(const std::vector<T> input) {

	}


	// assignment operator

	// destructor
	~C() { std::out << "destructor" << std::endl; }


};



int main() {

}


