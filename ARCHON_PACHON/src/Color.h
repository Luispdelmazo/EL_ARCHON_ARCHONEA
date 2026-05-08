#pragma once
#include <freeglut.h>
using uchar = unsigned char;
struct Color
{
	uchar r{ 255 }, g{ 255 }, b{ 255 };
	void pon_color() const
	{
		glColor3ub(r, g, b);
	}
};

