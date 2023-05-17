#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <memory>

#include "IODevice.h"

// base shape class
class Shape
{
public:
	virtual void display(IODevice& ioDevice) const = 0;
};

class Circle : public Shape
{
public:
	void display(IODevice& ioDevice) const override {
		ioDevice << *this;
	}
};

class Line : public Shape
{
public:
	void display(IODevice& ioDevice) const override
	{
		ioDevice << *this;
	}
};
