#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

//• Default initialisation : object is constructed without an initializer.
class DefaultInitClass {
private:
	int m_data;
public:
	DefaultInitClass() = default;
};

//• Value initialisation : object is constructed with an empty initializer.
class ValueInitClass {
private:
	int m_data;
public:
	ValueInitClass() { m_data = 3; }
};
 
//• Direct initialisation : object is initialised from an explicit set of constructor arguments.
class DirectInitClass {
private:
	int m_data;
public:
	DirectInitClass(int input) : m_data(input) {};
};

//• Copy initialisation : object is initialised from another object.
class CopyInitClass {
private:
	int m_data;
public:
	CopyInitClass() = default;
	CopyInitClass(int data) : m_data(data) {};
	CopyInitClass(CopyInitClass& copy) { m_data = copy.m_data; }
};

//• List initialisation : object is initialised from braced - init - list.
class ListInitClass {
private:
	int m_data[3];
public:
	ListInitClass(int a, int b, int c) : m_data{ a, b, c } {};
};

//• Aggregate initialisation : initialise an aggregate from a braced - init - list.
struct AggInitClass {
	int a; double b; char c;
};

//• Reference initialisation : bind a reference to an object.


struct S
{
	int x;
	struct Foo
	{
		int i; int j; int a[3];
	} b;
};

int main()
{
	/// PART A) Test the construction
	// default initialization
	DefaultInitClass c1;
	// value initialization
	ValueInitClass c2{};
	// direct initialization
	int data = 3;
	DirectInitClass c3(data);
	// copy initialization
	CopyInitClass c4(123);
	CopyInitClass c5(c4);
	// list initialization
	ListInitClass c6{ 3, 5, 7};
	// aggregate initialization
	AggInitClass c7 = { 4, 6.7, 'h'};
	// reference initialization
	int lvalue = 42;
	int& ref = lvalue;

	/// Part (B) Ill-formed cases
	// Some ill-formed cases include:
	// 1. Copy initialize an object that is not copyable or does not have a copy constructor.
	// 2. Using list initialization with incompatible types.
	// 3. Reference initialize a reference to a temporary object, namely, an rvalue
	// 4. Aggregate initialize a class where the data members are private, or class have defined constructors, or class has inheritance relationship


	/// Part (C) aggregate initialization of struct S
	S s1; // default
	S s2{}; // value
	S s3();
	S s4(s2); // copy
	// aggregate initialization of struct S
	S s = { 42, {1, 2, {3, 4, 5}} };
}

