#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
// MiguelHernando - Lider del Departamento de Automatica
// Hereda de Pieza con : public Pieza - ES una Pieza, no TIENE una Pieza 
// Teletransporte: puede ir a cualquier casilla del tablero
// Los conjuros son atributos suyos - no hace falta una clase aparte 

class MiguelHernando : public Pieza {
private:
    int conjurosRestantes;
    bool conjuroUsado[7]; // Cada conjuro solo se puede usar una vez por partida

public:
    MiguelHernando(int fila, int col)
        : Pieza("MiguelHernando", Bando::OSCURIDAD, TipoMovimiento::TELETRANSPORTE,
                fila, col, 100, 25, 3, 9, 2)
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

        // Esfera principal morada - mas grande que el resto
        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.5f, 0.0f, 0.8f);
        }
        glutSolidSphere(0.38f, 20, 20);

        glPopMatrix();
    }

    void habilidadEspecial() override {
        // Los conjuros se lanzan desde Juego con usarConjuro()
    }

    bool puedeUsarConjuro(int indice) {
        if (indice < 0 || indice >= 7) return false;
        return !conjuroUsado[indice];
    }

    void usarConjuro(int indice) {
        if (puedeUsarConjuro(indice)) {
            conjuroUsado[indice] = true;
            conjurosRestantes--;
        }
    }

    int getConjurosRestantes() const { return conjurosRestantes; }
};
