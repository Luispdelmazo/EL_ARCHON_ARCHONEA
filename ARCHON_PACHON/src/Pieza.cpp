#include "Pieza.h"

Pieza::Pieza(const Vector2D& pos, const Color& col, const int salud, const Movimiento& mov, const int desp) {
	posicion = pos;
	color = col;
	vida = salud;
	movimiento = mov;
	desplazamiento = desp;
}

void Pieza::dibuja() {

}

void Pieza::movimientos_posibles() {
	switch (movimiento) {
		case Movimiento::terrestre:

		case Movimiento::volador:
			for (auto i = posicion.x - desplazamiento; i <= posicion.x + desplazamiento; i++) {
				for (auto j = posicion.y - desplazamiento; j <= posicion.y + desplazamiento; j++) {
					if ((i >= 0 && j >= 0) && (i!=posicion.x || j!=posicion.y)) {
						glColor3f(1.0f, 0.5f, 0.0f);
						float desp_max=20;
						float desp_min=10;

						// Barra horizontal
						glBegin(GL_QUADS);
						glVertex3f(80 + i * 60 + desp_max, 80 + j * 60 + desp_min, 0.1);
						glVertex3f(80 + i * 60 + desp_min, 80 + j * 60 + desp_max, 0.1);
						glVertex3f(80 + i * 60 - desp_max, 80 + j * 60 - desp_min, 0.1);
						glVertex3f(80 + i * 60 - desp_min, 80 + j * 60 - desp_max, 0.1);
						glEnd();

						// Barra vertical
						glBegin(GL_QUADS);
						glVertex3f(80 + i * 60 + desp_max, 80 + j * 60 - desp_min, 0.1);
						glVertex3f(80 + i * 60 + desp_min, 80 + j * 60 - desp_max, 0.1);
						glVertex3f(80 + i * 60 - desp_max, 80 + j * 60 + desp_min, 0.1);
						glVertex3f(80 + i * 60 - desp_min, 80 + j * 60 + desp_max, 0.1);
						glEnd();
					}
				}
			}
			break;
		case Movimiento::teletransporte:
			for (auto i = posicion.x - desplazamiento; i <= posicion.x + desplazamiento; i++) {
				for (auto j = posicion.y - desplazamiento; j <= posicion.y + desplazamiento; j++) {
					if ((i >= 0 && j >= 0) && (i != posicion.x || j != posicion.y)) {
						glColor3f(1.0f, 0.5f, 0.0f);
						float desp_max = 20;
						float desp_min = 10;

						// Barra horizontal
						glBegin(GL_QUADS);
						glVertex3f(80 + i * 60 + desp_max, 80 + j * 60 + desp_min, 0.1);
						glVertex3f(80 + i * 60 + desp_min, 80 + j * 60 + desp_max, 0.1);
						glVertex3f(80 + i * 60 - desp_max, 80 + j * 60 - desp_min, 0.1);
						glVertex3f(80 + i * 60 - desp_min, 80 + j * 60 - desp_max, 0.1);
						glEnd();

						// Barra vertical
						glBegin(GL_QUADS);
						glVertex3f(80 + i * 60 + desp_max, 80 + j * 60 - desp_min, 0.1);
						glVertex3f(80 + i * 60 + desp_min, 80 + j * 60 - desp_max, 0.1);
						glVertex3f(80 + i * 60 - desp_max, 80 + j * 60 + desp_min, 0.1);
						glVertex3f(80 + i * 60 - desp_min, 80 + j * 60 + desp_max, 0.1);
						glEnd();
					}
				}
			}
			break;


	}

}