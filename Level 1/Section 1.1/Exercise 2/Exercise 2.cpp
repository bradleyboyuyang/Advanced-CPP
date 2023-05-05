#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<complex>

using namespace std;

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
	vector<int> vec{ 1,2,3,4,5 };
	int initVal = 1;

	// Part A) Implement and test algorithm using generic lambda
	// stl accumulate
	int acc2 = accumulate(vec.begin(), vec.end(), initVal, multiplies<int>());
	// function object
	int accA = accumulate(vec.begin(), vec.end(), initVal, FOMultiply());
	// lambda function
	int acc3 = accumulate(vec.begin(), vec.end(), initVal, MyMultiply);

	cout << acc2 << endl;
	cout << accA << endl;
	cout << acc3 << endl;

	// Using complex numbers
	using Complex = complex<double>;
	std::vector<Complex> complexArray{ Complex(1.0, 1.0), Complex(2.0, 2.0) };
	Complex initCVal(1.0, 1.0);
	// function object
	auto acc6C = accumulate(complexArray.begin(), complexArray.end(), initCVal, FOMultiply());
	// lambda function
	Complex acc6C_lambda = accumulate(complexArray.begin(), complexArray.end(), initCVal, MyMultiply);
	// template function
	Complex acc6C_template = accumulate(complexArray.begin(), complexArray.end(), initCVal, MyMultiply2<Complex>);
	cout << "Sum 6, complex numbers: " << acc6C << endl;
	cout << "Sum 6, complex numbers: " << acc6C_lambda << endl;
	cout << "Sum 6, complex numbers: " << acc6C_template << endl;
	// Yes, the algorithm can be used with complex numbers. We can use function objects, lambda function, or template function. 

	// Part B) Implement the accumulation algorithm using embedded lambda function
	for_each(vec.begin(), vec.end(), [&initVal](int& i) {initVal = MyMultiply(initVal, i); });
	for_each(complexArray.begin(), complexArray.end(), [&initCVal](Complex& i) {initCVal = MyMultiply(initCVal, i); });

	cout << initVal << endl;
	cout << initCVal << endl;
	// The results are the same as question (A).

	// Part C) Example of a stored lambda function that may be called from an STL algorithm
	// We use `transform` as the stl algorithm, `back_inserter` to iteratively insert elements at the end of a container
	vector<int> input{ 1,2,3,4,5 };
	auto square = [](int x) {return x * x; };
	vector<int> result;
	transform(input.begin(), input.end(), back_inserter(result), square);
	for (auto i : result) {
		cout << i << endl;
	}

}



