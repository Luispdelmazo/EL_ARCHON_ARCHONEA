#pragma once
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
	enum class Equipo { Alumnos , Profesores } equipo;// Luz , Oscuridad

public:
	Pieza(const Vector2D& pos, const Color& col, const int salud, const Movimiento& mov, const int desp);
	void dibuja();
	void movimientos_posibles();
};

