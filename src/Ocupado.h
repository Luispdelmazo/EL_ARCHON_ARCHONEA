#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// Ocupado - alumno siempre liado, movimiento volador
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: cada 5 ataques hace dano doble
// Visual: esfera azul con puntos alrededor - siempre ocupado con mil cosas

class Ocupado : public Pieza {
private:
    int contadorAtaques; // Cuenta los ataques para el dano doble

public:
    Ocupado(int fila, int col)
        : Pieza("Ocupado", Bando::LUZ, TipoMovimiento::VOLADOR,
                fila, col, 70, 14, 5, 4, 2)
    {
        contadorAtaques = 0;
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.3f, 0.5f, 0.9f);
        }
        glutSolidSphere(0.3f, 20, 20);

        // Puntos alrededor - simboliza que esta ocupado con mil cosas
        glColor3f(0.6f, 0.8f, 1.0f);
        float angulos[] = { 0.0f, 60.0f, 120.0f, 180.0f, 240.0f, 300.0f };
        for (int i = 0; i < 6; i++) {
            float rad = angulos[i] * 3.14159f / 180.0f;
            glPushMatrix();
            glTranslatef(0.38f * cosf(rad), 0.38f * sinf(rad), 0.0f);
            glutSolidSphere(0.06f, 8, 8);
            glPopMatrix();
        }

        glPopMatrix();
    }

    void habilidadEspecial() override {
        contadorAtaques++;
    }

    // Para que Batalla compruebe si toca dano doble
    bool deberiaDanoDoble() {
        return (contadorAtaques > 0 && contadorAtaques % 5 == 0);
    }

    int getContadorAtaques() const { return contadorAtaques; }
};
