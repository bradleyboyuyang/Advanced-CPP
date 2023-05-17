#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <memory>

#include "IODevice.h"
#include "Shape.h"
#include "Builder.h"

int main()
{
	/// Part (A) Create derived classes Circle and Line. Create I/O device classes to display CAD shapes in different ways.
	//See the implementation in `Shape.h` and `IODevice.h`

	/// Part (B) Create and test a number of builders and apply them in the current context
	// See the implementation in `Builder.h`
	// Use a Circle Builder that get the pointer to shape and ioDevice of a `circle`
	std::unique_ptr<Builder> builder = std::make_unique<CircleBuilder>();
	std::tuple<ShapePointer, IODevicePointer> product = builder->getProduct();
	ShapePointer shape = std::get<0>(product);
	IODevicePointer ioDevice = std::get<1>(product);
	// should output: console IO of circle
	shape->display(*ioDevice);
	// Use a Line Builder that get the pointer to shape and ioDevice of a `line`
	builder = std::make_unique<LineBuilder>();
	product = builder->getProduct();
	shape = std::get<0>(product);
	ioDevice = std::get<1>(product);
	// should output: svg IO of line
	shape->display(*ioDevice);

}

