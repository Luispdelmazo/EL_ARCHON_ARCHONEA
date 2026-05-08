#include "MiguelH.h"


MiguelH::MiguelH(double x, double y) {
    pieza.posicion = { x,y };
}

void MiguelH::dibuja() {
    glColor3ub(pieza.color.r, pieza.color.g, pieza.color.b);
    glPushMatrix();
    glTranslated(pieza.posicion.x, pieza.posicion.y, 0);
    glutSolidSphere(25, 20, 20);
    glPopMatrix();
}