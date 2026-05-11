#pragma once
#include "Vector2D.h"
#include "Color.h"

enum class Movimiento { terrestre, volador, teletransporte };
enum class Equipo { Alumnos, Profesores };// Luz , Oscuridad

class Pieza
{
	Vector2D posicion;
	Color color;
	int vida;
	Movimiento movimiento;
	int desplazamiento;
	Equipo equipo;

public:
	Pieza(const Vector2D& pos, const Equipo& equip, const Movimiento& mov=Movimiento::terrestre, const int desp=3, const int salud = 100);
	void dibuja();
	void movimientos_posibles();
	void colorea();
};

