#include "Oscar.h"

Oscar::Oscar(double x, double y) {
    pieza.posicion = { x,y };
}

void Oscar::dibuja() {
    glColor3ub(pieza.color.r, pieza.color.g, pieza.color.b);
    glPushMatrix();
    glTranslated(pieza.posicion.x, pieza.posicion.y, 0);
    glutSolidSphere(18, 20, 20);
    glPopMatrix();
}