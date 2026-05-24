#pragma once
#include <GL/glut.h>

class Proyectil {
private:
    float x, y;      // Posicion en la arena
    float vx, vy;    // Velocidad
    bool activo;     // Si esta en vuelo o no

public:
    Proyectil();
    // cada pieza dispara uno en la arena de combate 
    void disparar(float px, float py, float dvx, float dvy);
    void mover(float dt);
    void dibujar();
    float getX() const { return x; }
    float getY() const { return y; }
    bool getActivo() const { return activo; }
    void setActivo(bool a) { activo = a; }
};