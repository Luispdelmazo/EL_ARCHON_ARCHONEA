#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// Humilde - el alumno mas modesto, movimiento terrestre
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: sube sus stats al ganar una batalla
// Visual: esfera azul muy pequena - el peon del bando luz, hay varios

class Humilde : public Pieza {
public:
    Humilde(int fila, int col)
        : Pieza("Humilde", Bando::LUZ, TipoMovimiento::TERRESTRE,
                fila, col, 45, 8, 5, 2, 1)
    {}

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.5f, 0.7f, 1.0f); // Azul muy claro - modesto
        }
        // Mas pequeno que el resto - es el peon del bando luz
        glutSolidSphere(0.22f, 15, 15);

        glPopMatrix();
    }

    void habilidadEspecial() override {
        // Al ganar sube sus stats - se vuelve mas fuerte con la experiencia
        ataque    += 5;
        vidaMax   += 10;
        velocidad += 1;
    }
};
