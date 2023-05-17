#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <memory>

// Important: forward declaration in case of unknown class in IODevice
class Circle;
class Line;

// base IO class
class IODevice
{ // Interface for displaying CAD objects
public:
	virtual void operator << (const Circle& c) = 0;
	virtual void operator << (const Line& c) = 0;
};

class ConsoleIODevice : public IODevice {
public:
	void operator << (const Circle& c) override {
		std::cout << "Circle: Console IODevice evoked" << std::endl;
	}

	void operator << (const Line& c) override {
		std::cout << "Line: Console IODevice evoked" << std::endl;
	}
};

class SvgIODevice : public IODevice
{
public:
	void operator << (const class Circle& c) override
	{
		std::cout << "Circle: SVG IODevice evoked" << std::endl;
	}

	void operator << (const class Line& l) override
	{
		std::cout << "Line: SVG IODevice evoked" << std::endl;
	}
};