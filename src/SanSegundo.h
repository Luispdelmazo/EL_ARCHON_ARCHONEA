#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// SanSegundo - profe volador misterioso del departamento
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: puede dividirse en 2 una vez por partida subiendo sus stats
// Visual: dos esferas pequenas moradas juntas - representa la division

class SanSegundo : public Pieza {
private:
    bool divisionUsada; // Solo puede dividirse una vez

public:
    SanSegundo(int fila, int col)
        : Pieza("SanSegundo", Bando::OSCURIDAD, TipoMovimiento::VOLADOR,
                fila, col, 65, 15, 6, 4, 2)
    {
        divisionUsada = false;
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
            glutSolidSphere(0.35f, 20, 20);
        } else {
            // Dos esferas juntas - representa que puede dividirse
            glColor3f(0.6f, 0.0f, 0.8f);
            glPushMatrix();
            glTranslatef(-0.15f, 0.0f, 0.0f);
            glutSolidSphere(0.22f, 15, 15);
            glPopMatrix();

            glPushMatrix();
            glTranslatef( 0.15f, 0.0f, 0.0f);
            glutSolidSphere(0.22f, 15, 15);
            glPopMatrix();
        }

        glPopMatrix();
    }

    void habilidadEspecial() override {
        // Division - sube sus stats al usarla
        if (!divisionUsada) {
            vidaMax       += 20;
            vidaActual    += 20;
            ataque        += 5;
            divisionUsada  = true;
        }
    }

    bool getDivisionUsada() const { return divisionUsada; }
};
