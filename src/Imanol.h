#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// Imanol - peon del departamento, hay varios en el tablero
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: sus ataques pueden paralizar al rival un turno
// Visual: esfera pequena morada oscura - son muchos pero debiles

class Imanol : public Pieza {
private:
    bool puedeParalizar; // Puede paralizar una vez por batalla

public:
    Imanol(int fila, int col)
        : Pieza("Imanol", Bando::OSCURIDAD, TipoMovimiento::TERRESTRE,
                fila, col, 50, 10, 5, 2, 1)
    {
        puedeParalizar = true;
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.35f, 0.0f, 0.45f); // Morado muy oscuro - peon
        }
        // Mas pequeno que el resto - es el peon del bando oscuridad
        glutSolidSphere(0.25f, 15, 15);

        glPopMatrix();
    }

    void habilidadEspecial() override {
        // Paraliza al rival - se gestiona desde Batalla
        puedeParalizar = true;
    }

    bool getPuedeParalizar() const { return puedeParalizar; }
    void usarParalisis()           { puedeParalizar = false; }
};
