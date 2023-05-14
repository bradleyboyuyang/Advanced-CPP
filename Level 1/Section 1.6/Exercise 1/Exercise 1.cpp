#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

struct Base
{
	virtual void draw() { std::cout << "print a base\n"; }
	void print() { std::cout << "base print\n"; }
	~Base() { std::cout << "bye base\n"; }
};
struct Derived : public Base
{
	Derived() {}
	void draw() override
	{
		std::cout << "print a derived\n";
	}
	void draw() const {}

	~Derived() { std::cout << "bye derived\n"; }
};
class Derived2 final : public Derived
{
};

int main() {
	/// Part (A) Fix this code without removing any of the (perceived) functionality
	// We remove the print() in Derived since no additional function is added
	// we delete `override` from `draw() const override {}` since no parent function exists
	// we define Derived2 as final, since final class cannot be inherited


	/// Part (B) create instances of Derived using Base smart pointers. Check the output.
	std::shared_ptr<Base> base_ptr(new Base());
	std::shared_ptr<Base> derive_ptr(new Derived());
	base_ptr->draw();
	derive_ptr->draw();
	base_ptr->print();
	derive_ptr->print();

}
