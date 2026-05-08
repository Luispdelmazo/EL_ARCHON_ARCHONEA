#include "Ocupado.h"

Ocupado::Ocupado(double x, double y) {
    pieza.posicion = { x,y };
}

void Ocupado::dibuja() {
    glColor3ub(pieza.color.r, pieza.color.g, pieza.color.b);
    glPushMatrix();
    glTranslated(pieza.posicion.x, pieza.posicion.y, 0);
    glutSolidSphere(15, 20, 20);
    glPopMatrix();
}