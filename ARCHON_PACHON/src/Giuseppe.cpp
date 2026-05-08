#include "Giuseppe.h"

Giuseppe::Giuseppe(double x, double y) {
    pieza.posicion = { x,y };
}

void Giuseppe::dibuja() {
    glColor3ub(pieza.color.r, pieza.color.g, pieza.color.b);
    glPushMatrix();
    glTranslated(pieza.posicion.x, pieza.posicion.y, 0);
    glutSolidSphere(12, 20, 20);
    glPopMatrix();
}
