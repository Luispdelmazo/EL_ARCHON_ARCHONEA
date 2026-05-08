#pragma once
#include "Pieza.h"

class Ausente
{
	Pieza pieza{ {140,80}, {200,200,200}, 150, Movimiento::terrestre, 3 };

public:
	Ausente(double x, double y);

	void dibuja();
};

