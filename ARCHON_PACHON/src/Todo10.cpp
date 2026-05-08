#include "Todo10.h"

Todo10::Todo10(double x, double y) {
    pieza.posicion = { x,y };
}

void Todo10::dibuja() {
    glColor3ub(pieza.color.r, pieza.color.g, pieza.color.b);
    glPushMatrix();
    glTranslated(pieza.posicion.x, pieza.posicion.y, 0);
    glutSolidSphere(22, 20, 20);
    glPopMatrix();
}