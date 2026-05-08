#include "HectorM.h"

HectorM::HectorM(double x, double y) {
    pieza.posicion = { x,y };
}

void HectorM::dibuja() {
    glColor3ub(pieza.color.r, pieza.color.g, pieza.color.b);
    glPushMatrix();
    glTranslated(pieza.posicion.x, pieza.posicion.y, 0);
    glutSolidSphere(28, 20, 20);
    glPopMatrix();
}
