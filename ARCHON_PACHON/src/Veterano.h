#pragma once
#include "Pieza.h"
class Veterano
{
	Pieza pieza{ {80,200}, {200,200,200}, 300, Movimiento::terrestre, 3 };

public:
	Veterano(double x, double y);

	void dibuja();
};

