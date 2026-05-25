#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// Mago - alumno con poderes, movimiento volador
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: sobrevive el primer golpe mortal con 1 de vida
// Sobreescribimos recibirDano igual que EsferaPulsante sobreescribia mueve en el Pang

class Mago : public Pieza {
private:
    bool escudoActivo; // El escudo que le salva de morir una vez

public:
    Mago(int fila, int col)
        : Pieza("Mago", Bando::LUZ, TipoMovimiento::VOLADOR,
                fila, col, 65, 22, 5, 4, 2)
    {
        escudoActivo = true;
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

        // Octaedro encima - simbolo de magia
        if (escudoActivo) {
            glColor3f(0.8f, 0.8f, 1.0f); // Brillante cuando el escudo esta activo
        } else {
            glColor3f(0.3f, 0.3f, 0.5f); // Apagado cuando ya lo usó
        }
        glPushMatrix();
        glTranslatef(0.0f, 0.38f, 0.0f);
        glScalef(0.4f, 0.4f, 0.4f);
        glutSolidOctahedron();
        glPopMatrix();

        glPopMatrix();
    }

    // Sobreescribimos recibirDano para implementar el escudo
    // Igual que en el Pang EsferaPulsante sobreescribia mueve()
    void recibirDano(int dano) override {
        if (escudoActivo && vidaActual - dano <= 0) {
            vidaActual   = 1;
            escudoActivo = false;
        } else {
            vidaActual -= dano;
            if (vidaActual <= 0) {
                vidaActual = 0;
                estaViva   = false;
            }
        }
    }

    void habilidadEspecial() override {
        // La habilidad se activa automaticamente en recibirDano
    }

    bool getEscudoActivo() const { return escudoActivo; }
};
