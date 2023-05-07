#include <iostream>
#include <array>
#include <algorithm>

class Shape
{
public:
	virtual void rotate(double d) = 0;
};
class Circle : public Shape
{
public:
	void rotate(double d) override { std::cout << "c\n"; }
};
class Line : public Shape
{
public:
	void rotate(double d) override { std::cout << "l\n"; }
};

class Valve
{
public:
	void rotate(double d) { std::cout << "v\n"; }
};

template <typename T>
void rotate(double d, T& arg) {
	// Reload terminate version of variadic function
	arg.rotate(d);
}

template <typename T, typename... Types>
void rotate(double d, T& arg, Types&... args)
{
	arg.rotate(d);
	rotate(d, args...);
}


int main() {
	/// Part (A) implement variadic template function `rotate()` for each possible combination of number of arguments
	Circle circle;
	Line line;
	Valve valve;
	double factor = 2.0;
	// We can in essence create compile-time aggregates/whole
	// part objects on the fly. We only need to write one function.
	rotate(factor, circle);
	rotate(factor, circle, line);
	rotate(factor, circle, valve);
	rotate(factor * 2, circle, valve, line);

	std::cout << "End of part (A)" << std::endl;

	/// Part (B)
	rotate(3.0, circle);
	rotate(5.0, line);
	rotate(5.0, valve);

	std::cout << "End of part (B)" << std::endl;

	/// Part (C)
	// The other way of doing it.
	std::array<Shape*, 5>shapeList{ &circle, &line, &circle, &circle, &line };
	double factor2 = 20.0;
	for (auto& elem : shapeList)
	{
		elem->rotate(factor2);
	}
	// Why can we not include valves in this array ?
	// The array initialization with `<Shape*, 5>` indicates that all array members should be 
	// instances of the Shape class. Yet the Valve class is not derived from class Shape.

	// And why can we include valves in the variadic approach ?
	// In variadic approach, we use the variadic template to capture any object whose
	// class implements the member function `rotate()`. Therefore we can include valves.

}

