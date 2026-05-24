#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// OscarC - profe terrestre que se hace mas fuerte con victorias
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: ataque vida y velocidad aumentan con cada batalla ganada
// Visual: esfera morada que crece y cambia de color con las victorias

class OscarC : public Pieza {
private:
    int batallasGanadas;
    float tamano; // Crece visualmente con cada victoria

public:
    OscarC(int fila, int col)
        : Pieza("OscarC", Bando::OSCURIDAD, TipoMovimiento::TERRESTRE,
                fila, col, 80, 16, 4, 3, 1)
    {
        batallasGanadas = 0;
        tamano          = 0.32f;
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            // Cambia de color segun las batallas ganadas
            if (batallasGanadas == 0) {
                glColor3f(0.5f, 0.0f, 0.5f);
            } else if (batallasGanadas == 1) {
                glColor3f(0.7f, 0.0f, 0.3f);
            } else {
                glColor3f(0.9f, 0.0f, 0.1f); // Casi rojo con muchas victorias
            }
        }
        glutSolidSphere(tamano, 20, 20);

        glPopMatrix();
    }

    void habilidadEspecial() override {
        // Sube stats al ganar una batalla
        batallasGanadas++;
        ataque    += 3;
        vidaMax   += 5;
        vidaActual = vidaMax;
        velocidad += 1;
        tamano    += 0.04f; // Crece visualmente
    }

    int getBatallasGanadas() const { return batallasGanadas; }
};
