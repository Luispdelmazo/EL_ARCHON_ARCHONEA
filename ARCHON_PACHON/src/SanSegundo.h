#pragma once
#include "Pieza.h"
class SanSegundo
{
	Pieza pieza{ {0,0}, {50,50,50}, 200, Movimiento::volador, 3 };

public:
	SanSegundo(double x, double y);

	void dibuja();
};

