#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// Ausente - alumno que nunca va a clase, movimiento terrestre
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: ataque se duplica cuando vida baja del 50%
// Sobreescribimos recibirDano igual que Mago - patron del Pang

class Ausente : public Pieza {
private:
    bool habilidadActivada; // Solo se activa una vez

public:
    Ausente(int fila, int col)
        : Pieza("Ausente", Bando::LUZ, TipoMovimiento::TERRESTRE,
                fila, col, 75, 12, 4, 3, 1)
    {
        habilidadActivada = false;
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            // Cambia a rojo cuando activa la habilidad
            if (habilidadActivada) {
                glColor3f(1.0f, 0.3f, 0.3f);
            } else {
                glColor3f(0.4f, 0.6f, 0.9f);
            }
        }
        glutSolidSphere(0.32f, 20, 20);

        glPopMatrix();
    }

    // Sobreescribimos recibirDano - mismo patron que Mago con su escudo
    void recibirDano(int dano) override {
        vidaActual -= dano;
        if (vidaActual <= 0) {
            vidaActual = 0;
            estaViva   = false;
            return;
        }
        // Si baja del 50% duplica el ataque una sola vez
        if (!habilidadActivada && vidaActual < vidaMax / 2) {
            ataque           *= 2;
            habilidadActivada = true;
        }
    }

    void habilidadEspecial() override {
        // Se activa automaticamente en recibirDano
    }

    bool getHabilidadActivada() const { return habilidadActivada; }
};
