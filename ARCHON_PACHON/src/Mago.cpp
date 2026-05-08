#include "Mago.h"

Mago::Mago(double x, double y) {
    pieza.posicion = { x,y };
}

void Mago::dibuja() {
    glColor3ub(pieza.color.r, pieza.color.g, pieza.color.b);
    glPushMatrix();
    glTranslated(pieza.posicion.x, pieza.posicion.y, 0);
    glutSolidSphere(20, 20, 20);
    glPopMatrix();
}