#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<complex>

auto MyMultiply = [](auto x, auto y) { return x * y; };

template <typename T>
T MyMultiply2(const T& x, const T& y) { return x * y; };


struct FOMultiply
{
	template <typename T>
	T operator () (const T& x, const T& y)
	{
		return x * y;
	}
};

int main() {
	std::vector<int> vec{ 1,2,3,4,5 };
	int initVal = 1;

	/// Part A) Implement and test algorithm using generic lambda
	// stl accumulate
	int acc2 = std::accumulate(vec.begin(), vec.end(), initVal, std::multiplies<int>());
	// function object
	int accA = std::accumulate(vec.begin(), vec.end(), initVal, FOMultiply());
	// lambda function
	int acc3 = std::accumulate(vec.begin(), vec.end(), initVal, MyMultiply);

	std::cout << acc2 << std::endl;
	std::cout << accA << std::endl;
	std::cout << acc3 << std::endl;

	// Using complex numbers
	using Complex = std::complex<double>;
	std::vector<Complex> complexArray{ Complex(1.0, 1.0), Complex(2.0, 2.0) };
	Complex initCVal(1.0, 1.0);
	// function object
	auto acc6C = accumulate(complexArray.begin(), complexArray.end(), initCVal, FOMultiply());
	// lambda function
	Complex acc6C_lambda = accumulate(complexArray.begin(), complexArray.end(), initCVal, MyMultiply);
	// template function
	Complex acc6C_template = accumulate(complexArray.begin(), complexArray.end(), initCVal, MyMultiply2<Complex>);
	std::cout << "Sum 6, complex numbers: " << acc6C << std::endl;
	std::cout << "Sum 6, complex numbers: " << acc6C_lambda << std::endl;
	std::cout << "Sum 6, complex numbers: " << acc6C_template << std::endl;
	// Yes, the algorithm can be used with complex numbers. We can use function objects, lambda function, or template function. 

	/// Part B) Implement the accumulation algorithm using embedded lambda function
	std::for_each(vec.begin(), vec.end(), [&initVal](int& i) {initVal = MyMultiply(initVal, i); });
	std::for_each(complexArray.begin(), complexArray.end(), [&initCVal](Complex& i) {initCVal = MyMultiply(initCVal, i); });

	std::cout << initVal << std::endl;
	std::cout << initCVal << std::endl;
	// The results are the same as question (A).

	/// Part C) Example of a stored lambda function that may be called from an STL algorithm
	// We use `transform` as the stl algorithm, `back_inserter` to iteratively insert elements at the end of a container
	std::vector<int> input{ 1,2,3,4,5 };
	auto square = [](int x) {return x * x; };
	std::vector<int> result;
	std::transform(input.begin(), input.end(), std::back_inserter(result), square);
	for (auto i : result) {
		std::cout << i << std::endl;
	}

}



