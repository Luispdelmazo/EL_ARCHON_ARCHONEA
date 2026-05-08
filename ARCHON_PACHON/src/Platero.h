#pragma once
#include "Pieza.h"
class Platero
{
	Pieza pieza{ {0,0}, {50,50,50}, 250, Movimiento::volador, 4 };

public:
	Platero(double x, double y);
	void dibuja();
};

