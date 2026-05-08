#pragma once
#include "Pieza.h"
class Ocupado
{
	Pieza pieza{ {80,80}, {200,200,200}, 200, Movimiento::volador, 3 };

public:
	Ocupado(double x, double y);

	void dibuja();
};

