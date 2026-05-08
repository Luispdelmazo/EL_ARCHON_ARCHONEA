#include "Pieza.h"

Pieza::Pieza(const Vector2D& pos, const Color& col, const int salud, const Movimiento& mov, const int desp) {
	posicion = pos;
	color = col;
	vida = salud;
	movimiento = mov;
	desplazamiento = desp;
}