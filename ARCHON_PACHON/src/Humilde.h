#pragma once
#include "Pieza.h"
class Humilde
{
	Pieza pieza{ {140,320}, {200,200,200}, 100, Movimiento::terrestre, 3 };

public:
	Humilde(double x, double y);
	void dibuja();
};

