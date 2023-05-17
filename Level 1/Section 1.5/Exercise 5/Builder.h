#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <memory>

#include "IODevice.h"
#include "Shape.h"

/// Part (B) Create and test a number of builders and apply them in the current context
// shared pointers that point to the base class `Shape` and `IODevice`
using ShapePointer = std::shared_ptr<Shape>;
using IODevicePointer = std::shared_ptr<IODevice>;

class Builder
{ // A Builder hierarchy that builds shapes and io devices
public:
	std::tuple<ShapePointer, IODevicePointer> getProduct()
	{ // GOF (!) Template Method pattern
		ShapePointer shape = getShape();
		IODevicePointer ioDevice = getIODevice();
		return std::make_tuple(shape, ioDevice);
	}
	// Hook functions that derived classes must implement
	virtual ShapePointer getShape() = 0;
	virtual IODevicePointer getIODevice() = 0;
};

class CircleBuilder : public Builder
{
public:
	ShapePointer getShape() {
		return std::make_shared<Circle>();
	}
	IODevicePointer getIODevice() {
		return std::make_shared<ConsoleIODevice>();
	}
};

class LineBuilder : public Builder
{
public:
	ShapePointer getShape() override
	{
		return std::make_shared<Line>();
	}

	IODevicePointer getIODevice() override
	{
		return std::make_shared<SvgIODevice>();
	}
};
