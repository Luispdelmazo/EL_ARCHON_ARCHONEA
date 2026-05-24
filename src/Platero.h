#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// Platero - profe volador del departamento
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: su zona de dano crece en combate cuantos mas turnos pasan
// Visual: esfera morada con alas - volador del bando oscuridad

class Platero : public Pieza {
private:
    int turnosCombate; // Su alcance crece con los turnos

public:
    Platero(int fila, int col)
        : Pieza("Platero", Bando::OSCURIDAD, TipoMovimiento::VOLADOR,
                fila, col, 75, 18, 5, 4, 2)
    {
        turnosCombate = 0;
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.6f, 0.1f, 0.9f); // Morado claro
        }
        glutSolidSphere(0.3f, 20, 20);

        // Alas - marca que es volador
        glColor3f(0.4f, 0.0f, 0.6f);
        glBegin(GL_TRIANGLES);
        glVertex3f(-0.15f,  0.0f, 0.0f);
        glVertex3f(-0.45f,  0.2f, 0.0f);
        glVertex3f(-0.45f, -0.2f, 0.0f);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex3f( 0.15f,  0.0f, 0.0f);
        glVertex3f( 0.45f,  0.2f, 0.0f);
        glVertex3f( 0.45f, -0.2f, 0.0f);
        glEnd();

        glPopMatrix();
    }

    void habilidadEspecial() override {
        // La zona de dano crece con los turnos en combate
        turnosCombate++;
        alcanceAtaque += 1;
    }

    int getTurnosCombate() const { return turnosCombate; }
};
