#pragma once
#include "Pieza.h"
class Oscar
{
	Pieza pieza{ {0,0}, {50,50,50}, 250, Movimiento::terrestre, 4 };

public:
	Oscar(double x, double y);

	void dibuja();
};

