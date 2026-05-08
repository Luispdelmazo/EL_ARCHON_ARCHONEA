#pragma once
#include "Pieza.h"
class Basil
{
	Pieza pieza{ {0,0}, {50,50,50}, 200, Movimiento::volador, 5 };

public:
	Basil(double x, double y);

	void dibuja();
};

