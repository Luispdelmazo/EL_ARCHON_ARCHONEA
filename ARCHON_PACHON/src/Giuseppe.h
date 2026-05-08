#pragma once
#include "Pieza.h"
class Giuseppe
{
	Pieza pieza{ {0,0}, {50,50,50}, 150, Movimiento::terrestre, 3 };

public:
	Giuseppe (double x, double y);

	void dibuja();
};

