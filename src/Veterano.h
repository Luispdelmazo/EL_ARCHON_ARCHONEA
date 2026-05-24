#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// Veterano - alumno con experiencia, movimiento terrestre
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: su ataque sube cada vez que gana una batalla
// Visual: cubo solido azul oscuro - robusto y resistente

class Veterano : public Pieza {
private:
    int batallasGanadas; // Cada victoria le hace mas fuerte

public:
    Veterano(int fila, int col)
        : Pieza("Veterano", Bando::LUZ, TipoMovimiento::TERRESTRE,
                fila, col, 80, 15, 4, 3, 1)
    {
        batallasGanadas = 0;
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.1f, 0.2f, 0.7f); // Azul oscuro
        }
        glutSolidCube(0.6f);

        glPopMatrix();
    }

    void habilidadEspecial() override {
        // Su ataque sube al ganar batallas
        batallasGanadas++;
        ataque += 5;
    }

    int getBatallasGanadas() const { return batallasGanadas; }
};
