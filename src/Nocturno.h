#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// Nocturno - alumno misterioso, movimiento terrestre
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: puede duplicar velocidad una vez por batalla
// Visual: esfera azul muy oscura con punto brillante interior

class Nocturno : public Pieza {
private:
    bool velocidadDuplicada; // Solo puede duplicar una vez por batalla

public:
    Nocturno(int fila, int col)
        : Pieza("Nocturno", Bando::LUZ, TipoMovimiento::TERRESTRE,
                fila, col, 70, 18, 6, 2, 1)
    {
        velocidadDuplicada = false;
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        // Esfera exterior oscura
        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.05f, 0.05f, 0.3f); // Azul casi negro
        }
        glutSolidSphere(0.35f, 20, 20);

        // Punto brillante interior - efecto de brillo nocturno
        glColor3f(0.5f, 0.5f, 1.0f);
        glutSolidSphere(0.12f, 10, 10);

        glPopMatrix();
    }

    void habilidadEspecial() override {
        if (!velocidadDuplicada) {
            velocidad         *= 2;
            velocidadDuplicada = true;
        }
    }

    bool getVelocidadDuplicada() const { return velocidadDuplicada; }
    void resetHabilidad()              { velocidadDuplicada = false; }
};
