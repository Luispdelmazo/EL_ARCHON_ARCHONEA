#pragma once
#include "Pieza.h"
class Mago
{
	Pieza pieza{ {80,260}, {200,200,200}, 200, Movimiento::volador, 5 };

public:
	Mago(double x, double y);

	void dibuja();
};

