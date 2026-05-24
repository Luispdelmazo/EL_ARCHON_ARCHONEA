#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// HectorMontes - profe terrestre, el mas resistente del departamento
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: recupera 1 punto de vida por segundo en batalla
// Visual: cubo morado con cruz verde - simbolo de curacion

class HectorMontes : public Pieza {
private:
    float timerCuracion; // Timer para curar cada segundo

public:
    HectorMontes(int fila, int col)
        : Pieza("HectorMontes", Bando::OSCURIDAD, TipoMovimiento::TERRESTRE,
                fila, col, 90, 14, 3, 3, 1)
    {
        timerCuracion = 0.0f;
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.4f, 0.0f, 0.6f); // Morado oscuro
        }
        glutSolidCube(0.6f);

        // Cruz verde encima - simbolo de curacion
        glColor3f(0.0f, 0.8f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-0.25f,  0.05f, 0.35f);
        glVertex3f( 0.25f,  0.05f, 0.35f);
        glVertex3f( 0.25f, -0.05f, 0.35f);
        glVertex3f(-0.25f, -0.05f, 0.35f);
        glVertex3f(-0.05f,  0.25f, 0.35f);
        glVertex3f( 0.05f,  0.25f, 0.35f);
        glVertex3f( 0.05f, -0.25f, 0.35f);
        glVertex3f(-0.05f, -0.25f, 0.35f);
        glEnd();

        glPopMatrix();
    }

    void habilidadEspecial() override {
        curar(1);
    }

    // Batalla llama a esto con dt para curar cada segundo
    void actualizarCuracion(float dt) {
        timerCuracion += dt;
        if (timerCuracion >= 1.0f) {
            curar(1);
            timerCuracion = 0.0f;
        }
    }
};
