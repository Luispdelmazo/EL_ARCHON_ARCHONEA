#pragma once
#include "Pieza.h"
class Delegado
{
	Pieza pieza{ {80,320}, {200,200,200}, 250, Movimiento::teletransporte, 3 };

public:
	Delegado(double x, double y);

	void dibuja();
};

