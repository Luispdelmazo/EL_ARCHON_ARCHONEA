#pragma once
#include "Pieza.h"
class Nocturno
{
	Pieza pieza{ {80,140}, {200,200,200}, 250, Movimiento::terrestre, 4 };

public:
	Nocturno(double x, double y);

	void dibuja();
};

