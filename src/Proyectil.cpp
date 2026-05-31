#include "Proyectil.h"
Proyectil::Proyectil() {
    x = 0.0f;
    y = 0.0f;
    vx = 0.0f;
    vy = 0.0f;
    activo = false;
}
void Proyectil::disparar(float px, float py, float dvx, float dvy) {
    x = px;
    y = py;
    vx = dvx;
    vy = dvy;
    activo = true;
}
void Proyectil::mover(float dt) {
    if (!activo) return;
    x += vx * dt;
    y += vy * dt;
    // si sale de la arena se desactiva
    if (x < -4.5f || x > 4.5f || y < -4.5f || y > 4.5f) {
        activo = false;
    }
}
void Proyectil::dibujar() {
    if (!activo) return;
    glPushMatrix();
    glTranslatef(x, y, 0.1f);
    glColor3f(1.0f, 1.0f, 0.0f); // amarillo
    glutSolidSphere(0.1f, 10, 10);
    glPopMatrix();
}