#include "C.h"
#include "D.h"
#include "E.h"
#include "F.h"
#include "G.h"

#include<vector>
#include<array>


int main() {
	/// Test the class C implementation
	std::cout << "Test Basic Class C: " << std::endl;
	// default constructor
	C<double> C1;
	C1.print();

	// constructor
	Vec<double> testVec{ 1.0, 4.0, 6.0, 10.0 };
	double multiplier = 3;
	C<double> C2(testVec);
	C2.print();
	C2.scale(multiplier);
	C2.print();

	// copy constructor
	C<double> copy(Vec<double>{1.0, 2.0, 3.0, 4.0 });
	C<double> C3(copy);
	C3.print();
	C3.scale(multiplier);
	C3.print();

	// assignment operator
	C<double> C4 = copy;
	C4.print();
	C4.scale(multiplier);
	C4.print();

	/// Part (A) Test with modified class D
	std::cout << "Test Modified Class D: " << std::endl;
	// default constructor
	D<double> D1;
	D1.print();
	// constructor
	D<double> D2(Vec<double>{ 1.0, 4.0, 6.0, 10.0 });
	D2.print();

	// test copy constructor and assignment operator
	//D<double> copy2;
	//D<double> test = copy2;
	//D<double> D3(test);
	//D<double> D4;
	//D4 = test;
	// error saying inaccessible

	/// Part (B) Add explicit keyword to constructor to avoid implicit type conversion, see modified class E
	std::cout << "Test Modified Class E: " << std::endl;
	E<double> E1(Vec<double>{ 1.0, 4.0, 6.0, 10.0 });
	D<double> DTest = Vec<double>{ 1.0, 4.0, 6.0, 10.0 };
	//E<double> ETest = Vec<double>{ 1.0, 4.0, 6.0, 10.0 }; // error in implicit conversion for class E

	/// Part (C) Use constexpr keyword for certain functions, see modifed class F
	// we add constexpr to default constructor, normal constructor and the scale function
	// we use vector and array respectively to test the constexpr
	std::cout << "Test Modified Class F: " << std::endl;
	std::vector<double> initVec =  { 1.0, 3.0, 4.0 };
	F<std::vector<double>> F1(initVec);
	F1.print();
	F1.scale(multiplier);
	F1.print();

	std::array<double, 5> initArr = { 1.0, 3.0, 4.0, 6.0, 7.0 };
	F<std::array<double, 5>> F2(initArr);
	F2.print();
	F2.scale(multiplier);
	F2.print();

	/// Part (D) Use nonexcept for certain functions, see modified class G
	// For the member function, the scale function is not likely to throw an exception, the print may throw exception
	std::cout << "Test Modified Class G: " << std::endl;
	G<std::array<double, 3>> G1({ 1.0, 3.0, 4.0 });
	G1.print();
	G1.scale(multiplier);
	G1.print();

}


