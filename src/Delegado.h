#pragma once
#include "Pieza.h"
#include <GL/glut.h> 

// Delegado - Lider de los alumnos EE309
// Hereda de Pieza con : public Pieza - ES una Pieza, no TIENE una Pieza 
// Teletransporte: puede ir a cualquier casilla del tablero
// Los conjuros son atributos suyos - no hace falta una clase aparte 

class Delegado : public Pieza {
private:
    int conjurosRestantes;
    bool conjuroUsado[7]; // Cada conjuro solo se puede usar una vez por partida

public:
    Delegado(int fila, int col)
        : Pieza("Delegado", Bando::LUZ, TipoMovimiento::TELETRANSPORTE,
                fila, col, 100, 20, 3, 9, 2)
    {
        conjurosRestantes = 7;
        for (int i = 0; i < 7; i++) {
            conjuroUsado[i] = false;
        }
    }

    void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        // Anillo dorado debajo - marca que es el lider
        glColor3f(1.0f, 0.85f, 0.0f);
        glPushMatrix();
        glScalef(1.0f, 0.2f, 1.0f);
        glutSolidSphere(0.42f, 20, 20);
        glPopMatrix();

        // Esfera principal azul - mas grande que el resto
        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.2f, 0.4f, 1.0f);
        }
        glutSolidSphere(0.38f, 20, 20);

        glPopMatrix();
    }

    void habilidadEspecial() override {
        // Los conjuros se lanzan desde Juego con usarConjuro()
    }

    // Comprueba si un conjuro esta disponible
    bool puedeUsarConjuro(int indice) {
        if (indice < 0 || indice >= 7) return false;
        return !conjuroUsado[indice];
    }

    // Marca el conjuro como usado
    void usarConjuro(int indice) {
        if (puedeUsarConjuro(indice)) {
            conjuroUsado[indice] = true;
            conjurosRestantes--;
        }
    }

    int getConjurosRestantes() const { return conjurosRestantes; }
};
