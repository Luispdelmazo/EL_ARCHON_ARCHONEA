#pragma once
//Es el old
#include "Vector2D.h"
#include "Color.h"

enum class Movimiento { terrestre, volador, teletransporte };

class Pieza
{
	Vector2D posicion;
	Color color;
	int vida;
	Movimiento movimiento;
	int desplazamiento;

public:
	friend class Humilde;
	friend class Ausente;
	friend class Ocupado;
	friend class Nocturno;
	friend class Mago;
	friend class Veterano;
	friend class Todo10;
	friend class Delegado;
	friend class Imanol;
	friend class Giuseppe;
	friend class SanSegundo;
	friend class Oscar;
	friend class HectorM;
	friend class Basil;
	friend class Platero;
	friend class MiguelH;
	Pieza(const Vector2D& pos, const Color& col, const int salud, const Movimiento& mov, const int desp);

};

