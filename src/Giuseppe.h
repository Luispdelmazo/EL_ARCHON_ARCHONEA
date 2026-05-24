#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// Giuseppe - profe terrestre estricto del departamento
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: en sus combates no estan permitidas habilidades especiales
// Visual: cubo morado con borde negro - serio y estricto

class Giuseppe : public Pieza {
public:
    Giuseppe(int fila, int col)
        : Pieza("Giuseppe", Bando::OSCURIDAD, TipoMovimiento::TERRESTRE,
                fila, col, 85, 17, 3, 3, 1)
    {}

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
            glutSolidCube(0.65f);
        } else {
            // Cubo morado con borde negro - serio
            glColor3f(0.45f, 0.0f, 0.55f);
            glutSolidCube(0.6f);

            glColor3f(0.0f, 0.0f, 0.0f);
            glLineWidth(2.0f);
            glutWireCube(0.62f);
            glLineWidth(1.0f);
        }

        glPopMatrix();
    }

    void habilidadEspecial() override {
        // Sus combates anulan habilidades del rival - se gestiona en Batalla
    }

    // Batalla comprueba esto para saber si anular habilidades
    bool anulaHabilidades() const { return true; }
};
