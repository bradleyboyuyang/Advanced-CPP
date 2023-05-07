#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <bitset>

template <typename T>
void print(const T& arg) {
	// Reload terminate version of variadic function
	std::cout << "End of print " << arg << std::endl;
}

template <typename T, typename... Types>
void print(const T& arg, const Types&... args)
{
	std::cout << "Calling recursively, value: " << arg << ", ";
	print(args...);
}


int main() {
	/// Part (A) Create the template variadic function with its parameter pack
	// See the function code above

	/// Part (B) Create the termination/tail function
	// See the function code above

	/// Part (C) Test the function
	// Variadic function templates
	int j = 1; double d = 2.0;
	print(j); print(d); print(j, d); print(d, j);
	std::cout << "\n3 params \n";
	print(d, j, std::bitset<8>(233));


}