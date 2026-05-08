#include "Humilde.h"

Humilde::Humilde(double x, double y) {
    pieza.posicion = { x,y };
}

void Humilde::dibuja() {
    glColor3ub(pieza.color.r, pieza.color.g, pieza.color.b);
    glPushMatrix();
    glTranslated(pieza.posicion.x, pieza.posicion.y, 0);
    glutSolidSphere(10, 20, 20);
    glPopMatrix();
}
