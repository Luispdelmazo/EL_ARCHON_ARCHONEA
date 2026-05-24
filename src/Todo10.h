#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// Todo10 - el alumno que siempre saca 10, movimiento volador
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: copia las estadisticas del rival en combate
// Visual: esfera azul clara con alas trianguladas a los lados

class Todo10 : public Pieza {
private:
    bool habilidadUsada; // Solo copia una vez por batalla

public:
    Todo10(int fila, int col)
        : Pieza("Todo10", Bando::LUZ, TipoMovimiento::VOLADOR,
                fila, col, 75, 16, 5, 4, 2)
    {
        habilidadUsada = false;
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.4f, 0.6f, 1.0f); // Azul claro - volador
        }
        glutSolidSphere(0.3f, 20, 20);

        // Alas - marca que es volador
        glColor3f(0.6f, 0.8f, 1.0f);
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
        // Copia stats del rival - se gestiona en Batalla
        habilidadUsada = true;
    }

    // Para que Batalla pueda copiar las stats del rival
    void copiarStats(Pieza* rival) {
        if (!habilidadUsada && rival != nullptr) {
            ataque         = rival->getAtaque();
            velocidad      = rival->getVelocidad();
            alcanceAtaque  = rival->getAlcanceAtaque();
            habilidadUsada = true;
        }
    }

    bool getHabilidadUsada() const { return habilidadUsada; }
};
