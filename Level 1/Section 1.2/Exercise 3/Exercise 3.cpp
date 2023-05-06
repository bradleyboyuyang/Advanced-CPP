#include<iostream>
#include<vector>
#include<algorithm>

#include "C.h"

int main() {
	/// Part (A) Create move constructor and move assignment operator
	// See the updated C.h file

	/// Part (B) Test new functions
	// initialize an C object
	std::vector<double> initVec = { 2.0, 4.0, 4.0, 5.0, 1.0 };
	C<std::vector<double>> C1(initVec);

	// test move constructor
	C<std::vector<double>> C2(std::move(C1));
	C1.print();
	C2.print();
	// we can see the move constructor is called since C1 now becomes empty
	// test move assignment operation
	C<std::vector<double>> C3;
	C3 = std::move(C2);
	C2.print();
	C3.print();
	// we can see the move assignment operator is called since C2 now becomes empty

	/// Part (C) What happen if using an lvalue as the source of a move operation
	C<std::vector<double>> C4(C3);
	C3.print();
	C4.print();
	// In this case, we see the copy constructor is evoked instead of the move constructor



}