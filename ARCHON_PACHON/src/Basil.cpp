#include "Basil.h"

Basil::Basil(double x, double y) {
    pieza.posicion = { x,y };
}

void Basil::dibuja() {
    glColor3ub(pieza.color.r, pieza.color.g, pieza.color.b);
    glPushMatrix();
    glTranslated(pieza.posicion.x, pieza.posicion.y, 0);
    glutSolidSphere(20, 20, 20);
    glPopMatrix();
}