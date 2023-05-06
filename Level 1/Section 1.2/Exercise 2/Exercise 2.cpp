#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>

void printVec(std::vector<double> vec) {
	for (std::size_t i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

template < typename T >
void SwapCopyStyle(T& a, T& b)
{ // Swap a and b in copying way; temporary object needed
	T tmp(a); // Copy constructor
	a = b; // Copy all elements from b to a
	b = tmp; // Copy all elements from tmp to b
}

template<typename T>
void SwapMoveStyle(T& a, T& b)
{
	T tmp(std::move(a)); // move constructor
	a = std::move(b); // move all elements from b to a
	b = std::move(tmp); // move all elements from tmp to b
}



int main() {
	/// Part (A): Create a string and move to another string
	std::string origin{ "origin" };
	std::string target{ "target" };
	std::cout << "original string before move: " << origin << std::endl;
	std::cout << "target string before move: " << target << std::endl;
	target = std::move(origin);
	std::cout << "original string after move: " << origin << std::endl;
	std::cout << "target string after move: " << target << std::endl;
	// The original string becomes empty and the target string is replaced, which is memory efficient

	/// Part (B): Create a vector and move to another vector; compare the time with copy constructor
	std::vector<double> originVec(100000, 12);

	// check the time for copy constructor
	auto start_cp = std::chrono::high_resolution_clock::now();
	std::vector<double> copyVec{ originVec };
	auto end_cp = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_cp = end_cp - start_cp;
	std::cout << "Time for copy constructor£º" << elapsed_cp.count() << " milliseconds" << std::endl;

	// check the time for copy assignment operation
	std::vector<double> copyAssignVec;
	auto start_cpass = std::chrono::high_resolution_clock::now();
	copyAssignVec = originVec;
	auto end_cpass = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_cpass = end_cpass - start_cpass;
	std::cout << "Time for copy assignment£º" << elapsed_cpass.count() << " milliseconds" << std::endl;

	// check the time for move assignment
	std::vector<double> moveVec;
	auto start_mv = std::chrono::high_resolution_clock::now();
	moveVec = std::move(originVec);
	auto end_mv = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_mv = end_mv - start_mv;
	std::cout << "Time for move assignment£º" << elapsed_mv.count() << " milliseconds" << std::endl;

	/// Part (C) Define swap function with move semantics and compare performances
	// Two temporary copies. 
	// First is when the tmp variable is created, then when we assign tmp to b, tmp is returned and copied to b
	// The swap function using move semantics is defined as SwapMoveStyle(T& a, T& b)

	// create two large vectors
	std::vector<double> vec1(100000, 4321);
	std::vector<double> vec2(100000, 1234);

	// Time the copy-based swap
	auto start_copy = std::chrono::high_resolution_clock::now();
	SwapCopyStyle(vec1, vec2);
	auto end_copy = std::chrono::high_resolution_clock::now();
	auto time_copy = std::chrono::duration_cast<std::chrono::microseconds>(end_copy - start_copy);

	// Time the move-based swap
	auto start_move = std::chrono::high_resolution_clock::now();
	SwapMoveStyle(vec1, vec2);
	auto end_move = std::chrono::high_resolution_clock::now();
	auto time_move = std::chrono::duration_cast<std::chrono::microseconds>(end_move - start_move);

	// Print the results
	std::cout << "Copy-based swap took " << time_copy.count() << " microseconds." << std::endl;
	std::cout << "Move-based swap took " << time_move.count() << " microseconds." << std::endl;

	// We can see that move semantics is roughly two times more efficient since no temporary copies made 
}