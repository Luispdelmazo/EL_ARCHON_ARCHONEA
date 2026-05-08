#pragma once
#include "Pieza.h"
class HectorM
{
	Pieza pieza{ {0,0}, {50,50,50}, 300, Movimiento::terrestre, 3 };

public:
	HectorM(double x, double y);

	void dibuja();
};

