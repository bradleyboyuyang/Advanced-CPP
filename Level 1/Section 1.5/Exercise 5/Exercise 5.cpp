#include <iostream>
#include <vector>
#include <algorithm>

using ShapePointer = std::shared_ptr<Shape>;
using IODevicePointer = std::shared_ptr<IODevice>;

// Class hierarchy
class Shape
{
public:
	virtual void display(IODevice& ioDevice) const = 0;
};

class Circle : Shape
{
public:
	void display(IODevice& ioDevice) {

	}
};

class Line : Shape
{

};



class IODevice
{ // Interface for displaying CAD objects
public:
	virtual void operator << (const Circle& c) = 0;
	virtual void operator << (const Line& c) = 0;
};

class Builder
{ // A Builder hierarchy that builds shapes and io devices
public:
	std::tuple<ShapePointer, IODevicePointer> getProduct()
	{ // GOF (!) Template Method pattern
	// TBD
	}
	// Hook functions that derived classes must implement
	virtual ShapePointer getShape() = 0;
	virtual IODevicePointer getIODevice() = 0;
};



int main()
{
	/// Create derived classes Circle and Line. Create I/O device classes to display CAD shapes in different ways.




	/// Part (B) Create and test a number of builders and apply them in the current context



}

