#pragma once
#include "Pieza.h"
class Todo10
{
	Pieza pieza{ {80,380}, {200,200,200}, 250, Movimiento::volador, 4 };

public:
	Todo10(double x, double y);
	void dibuja();
};

