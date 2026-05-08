#pragma once
#include "Pieza.h"
class MiguelH
{
	Pieza pieza{ {0,0}, {50,50,50}, 250, Movimiento::teletransporte, 3 };

public:
	MiguelH(double x, double y);

	void dibuja();
};

