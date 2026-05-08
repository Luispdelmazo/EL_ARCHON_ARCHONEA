#pragma once
#include "Pieza.h"
class Imanol
{
	Pieza pieza{ {140,320}, {50,50,50}, 50, Movimiento::terrestre, 3 };

public:
	Imanol(double x, double y);
	void dibuja();
};

